#include "../include/main.h"
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
  printf("Successfully loaded %d test samples.\n", count);
}
