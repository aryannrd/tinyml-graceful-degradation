# import kagglehub
#
import os

import numpy as np
import pandas as pd
from scipy.stats import kurtosis

# measures peaks of the data compared to a standard bell curve.
# Download latest version
# path = kagglehub.dataset_download("vinayak123tyagi/bearing-dataset")
# print(path)
base_dir = "/Users/aryan/.cache/kagglehub/datasets/vinayak123tyagi/bearing-dataset/versions/1/2nd_test/2nd_test/"
directory = sorted(os.listdir(base_dir))
data_map = {
    "label": [],
    "mean_abs": [],
    "std_dev": [],
    "peak_to_peak": [],
    "kurtosis_data": [],
}

for num, file in enumerate(directory):
    file_path = os.path.join(base_dir, file)
    df = pd.read_csv(file_path, sep="\t", header=None)
    Bearing1 = df[0]
    features_list = []
    mean_abs = np.mean(np.abs(Bearing1))
    std_dev = np.std(Bearing1)
    peak_to_peak = np.ptp(Bearing1)  # peak to peak data, essentially max-min
    kurtosis_data = kurtosis(Bearing1)

    label = 0 if num < 700 else 1

    data_map["label"].append(label)
    data_map["mean_abs"].append(mean_abs)
    data_map["std_dev"].append(std_dev)
    data_map["peak_to_peak"].append(peak_to_peak)
    data_map["kurtosis_data"].append(kurtosis_data)

data_df = pd.DataFrame(data_map)
data_df.to_csv(
    path_or_buf="/Users/aryan/PycharmProjects/tinyml-graceful-degradation/data/bearingfeatures.csv",
    index=False,
)
