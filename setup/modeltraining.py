import os

import emlearn
import pandas as pd
from sklearn.calibration import calibration_curve
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.tree import DecisionTreeClassifier

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DATA_DIR = os.path.join(BASE_DIR, "data")

df = pd.read_csv(os.path.join(DATA_DIR, "bearingfeatures.csv"))

X = df.drop(columns=["label"])
y = df["label"]

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.25, random_state=42, stratify=y
)

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
c_compact.save(file="model_compact.h", name="model_compact")
