#include "../include/main.h"
#include "../include/model_compact.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAX_SAMPLES 300
#define NUM_FEATURES 4
float features[MAX_SAMPLES][NUM_FEATURES];
int labels[MAX_SAMPLES];

int main() {
  int count =
      parse_csv("/Users/aryan/PycharmProjects/tinyml-graceful-degradation/"
                "backup_data/test_features.csv",
                features, labels, MAX_SAMPLES);
  int16_t sample[NUM_FEATURES];
  int correct_count = 0;
  for (int i = 0; i < count; i++) {
    for (int j = 0; j < 4; j++) {
      sample[j] = (int16_t)(features[i][j]);
    }
    int result = model_compact_predict(sample, NUM_FEATURES);
    if (result == labels[i]) {
      correct_count += 1;
    }
  }
  printf("%d is the number of correct predictions out of %d. %.2f%% is the "
         "accuracy",
         correct_count, count, (float)correct_count / count * 100.0f);
  return 0;
}
