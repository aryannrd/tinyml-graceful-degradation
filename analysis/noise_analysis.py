import os

import matplotlib as plt
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from scipy.stats import t

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DATA_DIR = os.path.join(BASE_DIR, "backup_data")
df = pd.read_csv(os.path.join(DATA_DIR, "noise_results.csv"))
FIG_DIR = os.path.join(BASE_DIR, "figures")
os.makedirs(FIG_DIR, exist_ok=True)

df["recall"] = df["tp"] / (
    df["tp"] + df["fn"]
)  # true ones identified correctly by the model
df["f1"] = 2 * df["tp"] / (2 * df["tp"] + df["fp"] + df["fn"])
df["false_alarm"] = df["fp"] / (
    df["fp"] + df["tn"]
)  # number of times we raise an alarm when nothing is wrong

metrics = ["recall", "f1", "false_alarm"]
summary = df.groupby(["noise", "model"])[metrics].agg(["mean", "std", "count"])
print(summary)
# using t-distribution here for the extra uncertainity
error_const = t.ppf(0.975, 29)
models = {"full": "tab:blue", "compact": "tab:orange"}
labels = {"full": "Full model (RF)", "compact": "Compact model (DT)"}


def band(part, metric):
    """Mean and 95% CI half-width (t-distribution) for one metric."""
    mean = part[(metric, "mean")]
    std = part[(metric, "std")]
    n = part[(metric, "count")]
    half = t.ppf(0.975, n - 1) * std / np.sqrt(n)
    return mean, half


fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(11, 4.2), sharex=True)
for model, color in models.items():
    part = summary.xs(model, level="model")
    x = part.index

    mean, half = band(part, "f1")
    ax1.plot(x, mean, color=color, marker="o", label=labels[model])
    ax1.fill_between(x, mean - half, mean + half, color=color, alpha=0.2)

    mean, half = band(part, "recall")
    ax2.plot(x, mean, color=color, marker="o", label=f"{labels[model]}: recall")
    ax2.fill_between(x, mean - half, mean + half, color=color, alpha=0.2)

    mean, half = band(part, "false_alarm")
    ax2.plot(
        x,
        mean,
        color=color,
        marker="s",
        linestyle="--",
        label=f"{labels[model]}: false-alarm rate",
    )
    ax2.fill_between(x, mean - half, mean + half, color=color, alpha=0.2)


ax1.set(
    title="F1 under sensor noise",
    xlabel="Noise level (fraction of raw value)",
    ylabel="F1 (anomaly class)",
    ylim=(0, 1.05),
)
ax2.set(
    title="Missed failures vs. false alarms",
    xlabel="Noise level (fraction of raw value)",
    ylabel="Rate",
    ylim=(0, 1.05),
)
ax1.legend(loc="lower left")
ax2.legend(loc="center left", fontsize=8)
for ax in (ax1, ax2):
    ax.grid(alpha=0.3)
fig.text(
    0.5,
    -0.02,
    "Shaded: 95% CI of the mean over 30 repetitions",
    ha="center",
    fontsize=9,
)
fig.tight_layout()

fig.savefig(os.path.join(FIG_DIR, "e1_noise.pdf"), bbox_inches="tight")
fig.savefig(os.path.join(FIG_DIR, "e1_noise.png"), dpi=200, bbox_inches="tight")
plt.show()
