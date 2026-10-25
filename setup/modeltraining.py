import os

import emlearn
import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report
from sklearn.tree import DecisionTreeClassifier

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DATA_DIR = os.path.join(BASE_DIR, "backup_data")
INCLUDE_DIR = os.path.join(BASE_DIR, "edge_nodes", "include")

df = pd.read_csv(os.path.join(DATA_DIR, "bearingfeatures.csv"))

features = ["mean_abs", "std_dev", "peak_to_peak", "kurtosis_data"]
"""X = df.drop(columns=["label"]) * 10000
y = df["label"]
features = ["mean_abs", "std_dev", "peak_to_peak", "kurtosis_data"]
fig, axes = plt.subplots(len(features), 1, sharex=True, figsize=(10, 9))
for ax, name in zip(axes, features):
    ax.plot(df.index, df[name], linewidth=0.8)
    ax.set_xlim(left=450, right=700)
    ax.axvline(700, color="red", linestyle="--", label="current label boundary")
    ax.axvspan(650, 750, color="gray", alpha=0.2, label="dropped band")
    ax.set_ylabel(name)
fig.tight_layout()
plt.show()
"""
df = df.drop(index=range(530, 700))
df = df.drop(index=[982, 983])
GAP = 20
print(df.tail(10))


def time_test_split(part, train_frac=0.8):
    cut = int(len(part) * train_frac)
    return part.iloc[:cut], part.iloc[cut + GAP :]


normal = df[df["label"] == 0]
anomaly = df[df["label"] == 1]
n_train, n_test = time_test_split(normal)
a_train, a_test = time_test_split(anomaly)

train = pd.concat([n_train, a_train])
test = pd.concat([n_test, a_test])


X_test, y_test = test.drop(columns=["label"]), test["label"]
test_df = X_test.copy()
test_df["label"] = y_test
test_df.to_csv(
    os.path.join(DATA_DIR, "test_features.csv"), index=False
)  # unscaled saved


def calculate_multiplier(max_val):
    return 30000 / max_val


mean_mult = calculate_multiplier(train["mean_abs"].abs().max())
peak_to_peak_mult = calculate_multiplier(train["peak_to_peak"].abs().max())
kurtosis_mult = calculate_multiplier(train["kurtosis_data"].abs().max())
std_dev_mult = calculate_multiplier(train["std_dev"].abs().max())
features_mult = [mean_mult, std_dev_mult, peak_to_peak_mult, kurtosis_mult]
for i, j in zip(features, features_mult):
    train[i] = train[i] * j
    train[i] = train[i].round().clip(-32768, 32767)
    test[i] = test[i] * j
    test[i] = test[i].round().clip(-32768, 32767)


X_train, y_train = train.drop(columns=["label"]), train["label"]
X_test, y_test = (
    test.drop(columns=["label"]),
    test["label"],
)  # reassigned scaled for training

model_dt = DecisionTreeClassifier(max_depth=3, random_state=42)
model_rf = RandomForestClassifier(n_estimators=15, max_depth=5, random_state=42)
model_rf.fit(X_train, y_train)
model_dt.fit(X_train, y_train)

print("Random Forest")
print(classification_report(y_test, model_rf.predict(X_test)))
print("Compact Model (Decision Tree)")
print(classification_report(y_test, model_dt.predict(X_test)))


c_full = emlearn.convert(model_rf, method="inline")
c_full.save(file=os.path.join(INCLUDE_DIR, "model_full.h"), name="model_full")

c_compact = emlearn.convert(model_dt, method="inline")
emlearn_preds = c_compact.predict(X_test)
importance = model_dt.feature_importances_
importance2 = model_rf.feature_importances_
print(importance)
print(importance2)
c_compact.save(file=os.path.join(INCLUDE_DIR, "model_compact.h"), name="model_compact")

print("Sklearn accuracy:", accuracy_score(y_test, model_dt.predict(X_test)))
print("Emlearn accuracy:", accuracy_score(y_test, emlearn_preds))

with open(os.path.join(INCLUDE_DIR, "feature_scales.h"), "w") as file:
    file.write(f"""//auto generated from modeltraining, not to be edited. feature order is mean_abs, std_dev, peak_to_peak, and kurtosis_data
#ifndef FEATURE_SCALES_H
#define FEATURE_SCALES_H
#define NUM_FEATURES 4 \n
static const float FEATURE_SCALES[NUM_FEATURES] = {{{features_mult[0]}f,{features_mult[1]}f,{features_mult[2]}f,{features_mult[3]}f}};
#endif \n""")
