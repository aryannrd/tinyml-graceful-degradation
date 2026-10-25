#include "../include/main.h"
#include "../include/feature_scales.h"
#include "../include/model_compact.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#define MAX_SAMPLES 300
float features[MAX_SAMPLES][NUM_FEATURES];
int labels[MAX_SAMPLES];

int16_t clamp_to_int16(double value) {
  double rounded = round(value);
  if (rounded < -32768) {
    return -32768;
  } else if (rounded > 32767) {
    return 32767;
  }
  return (int16_t)rounded;
}

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
      for (int j = 0; j < NUM_FEATURES; j++) {
        double local = features[i][j];
        float wobble = (rand() % 200 - 100) / 100.0f;
        double added_noise = local * wobble * noise_step;
        local += added_noise;
        sample[j] = (clamp_to_int16(local * FEATURE_SCALES[j]));
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
