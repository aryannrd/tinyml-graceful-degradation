#include "../include/main.h"
#include "../include/model_compact.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#define MAX_SAMPLES 300
#define NUM_FEATURES 4
float features[MAX_SAMPLES][NUM_FEATURES];
int labels[MAX_SAMPLES];

int main() {
  srand(time(NULL));
  int count =
      parse_csv("/Users/aryan/PycharmProjects/tinyml-graceful-degradation/"
                "backup_data/test_features.csv",
                features, labels, MAX_SAMPLES);
  for (int step = 0; step < 10; step++) {
    float noise_step = step * 0.1;
    int16_t sample[NUM_FEATURES];
    int correct_count = 0;

    for (int i = 0; i < count; i++) {
      for (int j = 0; j < 4; j++) {
        sample[j] = (int16_t)(features[i][j]);
        float wobble = (rand() % 200 - 100) / 100.0f;
        int added_noise = sample[j] * wobble * noise_step;
        sample[j] += added_noise;
      }
      int result = model_compact_predict(sample, NUM_FEATURES);
      if (result == labels[i]) {
        correct_count += 1;
      }
    }
    printf("Noise %d0%% -> Correct: %d/%d, Accuracy: %.2f%%\n", step,
           correct_count, count, (float)correct_count / count * 100.0f);
  }
  return 0;
}
