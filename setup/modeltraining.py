import os

import emlearn
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.calibration import calibration_curve
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.tree import DecisionTreeClassifier

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DATA_DIR = os.path.join(BASE_DIR, "backup_data")

df = pd.read_csv(os.path.join(DATA_DIR, "bearingfeatures.csv"))


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
df = df.drop(index=range(530, 699))
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

X_train, y_train = train.drop(columns=["label"]) * 10000, train["label"]
X_test, y_test = test.drop(columns=["label"]) * 10000, test["label"]

test_df = X_test.copy()
test_df["label"] = y_test
test_df.to_csv(os.path.join(DATA_DIR, "test_features.csv"), index=False)

model_dt = DecisionTreeClassifier(max_depth=3, random_state=42)
model_rf = RandomForestClassifier(n_estimators=15, max_depth=5, random_state=42)
model_rf.fit(X_train, y_train)
model_dt.fit(X_train, y_train)

print("Random Forest")
print(classification_report(y_test, model_rf.predict(X_test)))
print("Compact Model (Decision Tree)")
print(classification_report(y_test, model_dt.predict(X_test)))


c_full = emlearn.convert(model_rf, method="inline")
c_full.save(file="model_full.h", name="model_full")

c_compact = emlearn.convert(model_dt, method="inline")
emlearn_preds = c_compact.predict(X_test)
importance = model_dt.feature_importances_
importance2 = model_rf.feature_importances_
print(importance)
print(importance2)
c_compact.save(file="model_compact.h", name="model_compact")

print("Sklearn accuracy:", accuracy_score(y_test, model_dt.predict(X_test)))
print("Emlearn accuracy:", accuracy_score(y_test, emlearn_preds))
