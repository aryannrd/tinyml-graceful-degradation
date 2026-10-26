#include "../include/main.h"
#include "../include/feature_scales.h"
#include "../include/model_compact.h"
#include "../include/model_full.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SAMPLES 300
#define NUM_REPS 30  // repetitions per noise level (seed = rep index)
#define NUM_STEPS 10 // noise levels 0.0, 0.1, ..., 0.9

float features[MAX_SAMPLES][NUM_FEATURES];
int labels[MAX_SAMPLES];

typedef struct {
  int tp, tn, fp, fn; // anomaly (1) is the positive class
} Counts;

int16_t clamp_to_int16(double value) {
  double rounded = round(value);
  if (rounded < -32768) {
    return -32768;
  } else if (rounded > 32767) {
    return 32767;
  }
  return (int16_t)rounded;
}

void tally(Counts *c, int pred, int label) {
  if (pred == 1 && label == 1)
    c->tp++;
  else if (pred == 0 && label == 0)
    c->tn++;
  else if (pred == 1 && label == 0)
    c->fp++;
  else
    c->fn++;
}

void write_row(FILE *out, int rep, double noise, const char *model, Counts c) {
  fprintf(out, "%d,%.2f,%s,%d,%d,%d,%d\n", rep, noise, model, c.tp, c.tn, c.fp,
          c.fn);
}

int main(void) {
  int count =
      parse_csv("/Users/aryan/PycharmProjects/tinyml-graceful-degradation/"
                "backup_data/test_features.csv",
                features, labels, MAX_SAMPLES);
  if (count <= 0) {
    fprintf(stderr, "No samples loaded\n");
    return 1;
  }

  FILE *out = fopen("/Users/aryan/PycharmProjects/tinyml-graceful-degradation/"
                    "backup_data/noise_results.csv",
                    "w");
  if (out == NULL) {
    perror("Failed to create output file");
    return 1;
  }
  fprintf(out, "rep,noise,model,tp,tn,fp,fn\n");

  for (int rep = 0; rep < NUM_REPS; rep++) {
    for (int step = 0; step < NUM_STEPS; step++) {
      srand((unsigned)(rep * NUM_STEPS + step));
      double noise_step = step * 0.1;
      Counts full = {0, 0, 0, 0};
      Counts compact = {0, 0, 0, 0};

      for (int i = 0; i < count; i++) {
        int16_t sample[NUM_FEATURES];
        for (int j = 0; j < NUM_FEATURES; j++) {
          double local = features[i][j];
          double wobble = (rand() % 200 - 100) / 100.0;
          local += local * wobble * noise_step;
          sample[j] = clamp_to_int16(local * FEATURE_SCALES[j]);
        }
        tally(&full, model_full_predict(sample, NUM_FEATURES), labels[i]);
        tally(&compact, model_compact_predict(sample, NUM_FEATURES), labels[i]);
      }
      write_row(out, rep, noise_step, "full", full);
      write_row(out, rep, noise_step, "compact", compact);

      if (rep == 0) {
        printf("noise %.1f  full %d/%d  compact %d/%d\n", noise_step,
               full.tp + full.tn, count, compact.tp + compact.tn, count);
      }
    }
  }
  fclose(out);
  printf("Wrote %d rows to backup_data/noise_results.csv\n",
         NUM_REPS * NUM_STEPS * 2);
  return 0;
}
