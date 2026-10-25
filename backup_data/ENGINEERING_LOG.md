# Engineering Log — TinyML Graceful Degradation

_Last updated: 2026-10-25 · newest entries at the top of each section_

Project: *Graceful Degradation of TinyML Inference Under Resource and Runtime Faults on Microcontrollers*.
Full plan: the "TinyML Graceful Degradation — Revised Plan" doc. This log tracks what was actually done, what broke, and why decisions were made.

---

## 1. Current status

| Phase | State |
| --- | --- |
| 1 — ML pipeline + emlearn export | Done; re-done after labeling/split fixes (Oct 24–25) |
| 2 — Single-node C runtime + fault sweeps | Started: CSV parser, fixed arrays, uniform-noise sweep on compact model |
| 2 — Per-feature int16 scaling fix | **Next**: designed, not implemented |
| 3 — C socket client + wire protocol | Not started (build Oct 31 – Nov 3 against the coordinator) |
| 4 — Rust/tokio coordinator | Learning tokio now; gate Nov 3 |
| 5–7 — Cascade, ESP32 (makerspace), paper | Not started; ESP32 is protected scope, EC2 dropped |

---

## 2. Work done

| Date | What |
| --- | --- |
| Oct 25 | Checked feature importances (see §5). Designed the per-feature scaling fix. |
| Oct 24 | Replaced random split with per-class time split + gap. Plotted features over time; relabeled with Option A (drop transition 530–699 and final 2 shutdown rows). |
| Oct 23 | Repo review. Found split leakage and int16 overflow. Revised plan: ESP32 kept, EC2 + cascade ablation dropped. |
| before Oct 23 | (git) Noise-injection sweep in C · fixed 28% accuracy bug with ×10000 scaling · C Makefile + `main.c` loading test samples into fixed arrays · C CSV parser · RF + DT trained and exported with emlearn · downloaded IMS data, built features for test 2 |

---

## 3. Dataset

- **Source:** NASA IMS bearing run-to-failure data, Kaggle mirror `vinayak123tyagi/bearing-dataset`.
- **Rig:** 4 bearings on one shaft, 2000 RPM, 6000 lb radial load, one accelerometer per bearing.
- **Recording:** every 10 min, a 1-second snapshot at 20 kHz (~20,480 samples) → one file.
- **Used:** test 2 (`2nd_test`), 984 files, about a week, ends with **bearing 1** outer-race failure. Column 0 = bearing 1.
- **Features (one row per file):** `mean_abs`, `std_dev`, `peak_to_peak`, `kurtosis` → `backup_data/bearingfeatures.csv` (984 rows, time-ordered).
- IMS has **no labels**. Labels are our rule (§4).

### What the timeline looks like (from the feature plot)

| Rows | Behaviour |
| --- | --- |
| 0 – ~530 | Flat — healthy |
| ~530 – 700 | Slow creep up in mean_abs / std_dev (early degradation) |
| 700 | Sharp step in all four features |
| ~700 – 780 | Elevated, then partial "recovery" dip |
| ~820 – ~980 | Rising again, accelerating after ~950 until failure |
| last 2 | All features ≈ 0 — rig switched off, not bearing data |

---

## 4. Labeling and split (decisions)

**Labeling — Option A (chosen):**

- Normal (0): rows 0–529
- Dropped as transition: rows 530–699
- Anomaly (1): rows 700 → end, minus the last 2 shutdown rows (dropped)

Rationale: only label rows we are sure about; ambiguous rows are excluded from both train and test. Paper wording: *"Snapshots before the first visible deviation are labeled normal, snapshots from the step change at 700 onward anomalous; the interval between is excluded as transitional."*

**Split — per-class time split with gap:**

- For each class separately: earlier 80% → train, skip a 20-snapshot gap, the rest → test.
- No shuffling (`train_test_split` removed). `random_state` was never the problem — shuffling time-series rows is: neighbouring snapshots are near-duplicates, so a shuffle leaks test rows into train.
- Test set: 87 normal, 37 anomaly (124 total). Report F1, not just accuracy.

**Known caveat:** the anomaly test rows are the last stretch before failure (most extreme), so they're easier to detect than earlier anomalies. State this in the paper. Optional stronger check later: test on another run (test 1 or 3).

---

## 5. Results so far

| Setup | RF acc | DT acc | Notes |
| --- | --- | --- | --- |
| Random stratified split (old) | ~98% | ~98% | **Leaky**: inflated by near-duplicate neighbours |
| Time split, drop 650–750 | 52% | 52% | Normal recall 0.42; normal test rows (540–649) sat in the creep zone → label problem, not model problem |
| Time split, Option A labels | **99.2%** | **99.2%** | Current baseline. F1 0.99 both classes. emlearn (Python) = sklearn = 99.19% |

**Feature importances (Option A):**

| Model | mean_abs | std_dev | peak_to_peak | kurtosis |
| --- | --- | --- | --- | --- |
| Decision tree (compact, depth 3) | 1.00 | 0 | 0 | 0 |
| Random forest (15 trees, depth 5) | 0.471 | 0.336 | 0.193 | 0.0005 |

Implications:

- Compact tree = one threshold on `mean_abs`. Faults on the other features can't change its output, so report which features faults are injected into.
- Hypothesis for E1: **under noise on mean_abs, the tree degrades faster than the forest** (forest spreads reliance over three features).
- Kurtosis is effectively unused.
- Idea for the quorum phase: give peers models trained on **different feature subsets** (e.g. one without mean_abs) so a single corrupted feature can't fool all peers (model diversity → less correlated failure).

---

## 6. Problems hit and fixes

| # | Problem | Cause | Fix / status |
| --- | --- | --- | --- |
| 1 | Accuracy 28% in C | Small float features (e.g. 0.06) cast to `int16_t` → 0 | ×10000 scaling (commit e730528). Superseded by #4 |
| 2 | 98% accuracy too good to trust | Random split leaked near-duplicate neighbouring snapshots | Per-class time split + 20-row gap. **Fixed** |
| 3 | 52% after fixing split; normals called anomalies | Row-700 label boundary too late: rows ~530–699 already degrading | Option A labels: drop 530–699. **Fixed** |
| 4 | int16 overflow in C | After ×10000, peak_to_peak reaches ~100,000 and kurtosis ~141,100 (21 rows > 32,767). Float→int16 out of range is undefined behaviour in C; Python emlearn `predict` uses floats, so the sklearn = emlearn check can't catch it | **Next.** Per-feature scales (see §7) |
| 5 | Shutdown rows labeled anomaly | Last 2 files ≈ 0 (rig off) | Dropped. **Fixed** |
| 6 | `emlearn_preds.feature_importances_` error | `emlearn_preds` is a predictions array; importances live on the sklearn model | Use `model_rf.feature_importances_` / `model_dt.feature_importances_` |
| 7 | Noise model mismatch | C sweep uses uniform multiplicative noise; plan says Gaussian | Open — pick one and state it in the paper |
| 8 | Regenerated `model_full.h` / `model_compact.h` land in repo root, but C includes `edge_nodes/include/` copies | `emlearn ... .save(file=...)` writes to cwd | Open — save into `edge_nodes/include/` so C never compiles against stale models |

---

## 7. Tech specifics

### Per-feature scaling fix (designed, to implement)

**Python (`setup/modeltraining.py`):**

1. After the split, per feature: `scale = 30000 / max(|feature|)` on **train only**.
2. Multiply train and test by these scales (replaces the single ×10000); train models on scaled data.
3. Generate `feature_scales.h` (array of 4 floats) from Python, never copy by hand.
4. Save `test_features.csv` as **raw, unscaled** values (like a real sensor).

**C (`edge_nodes/src/main.c`):**

1. `#include "feature_scales.h"`.
2. For each raw value: multiply by scale → clamp to [−32768, 32767] → cast to `int16_t` → model.
3. Inject sensor noise on the **raw float before scaling** (realistic; clamp then protects the cast).

**Verify:** C predictions match Python predictions on every test row, including the rows right before failure.

### Models

- Full: `RandomForestClassifier(n_estimators=15, max_depth=5, random_state=42)`
- Compact: `DecisionTreeClassifier(max_depth=3, random_state=42)`
- Exported with `emlearn.convert(..., method="inline")`; C signature `model_*_predict(const int16_t *features, int32_t features_length)`.

### Protocol (from plan, not built yet)

12-byte big-endian header: magic `0x544D` (2) · msg_type (1) · node_id (1) · payload_len (2) · flags (2) · sequence_id (4). Serialize field by field; shared golden-frame test file for C and Rust.

---

## 8. Next steps

1. Implement the per-feature scaling fix; confirm C == Python on all 124 test rows.
2. Fix model header output path (#8).
3. Write down the noise model choice (#7).
4. tokio: Hello Tokio → Spawning → Framing (write the 12-byte protocol spec before Framing).
5. Check makerspace for 3 identical ESP32s, Wi-Fi the boards can join, and a current meter.
