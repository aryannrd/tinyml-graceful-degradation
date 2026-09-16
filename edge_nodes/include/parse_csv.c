#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_csv(const char *path, float features[][4], int *labels,
              int max_rows) {
  FILE *file1 = fopen(path, "r");
  if (file1 == NULL) {
    perror("Failed to open file");
    return -1;
  }

  char buf[1000];
  int count = 0;

  fgets(buf, sizeof(buf), file1); // initializing the top label row

  while (fgets(buf, sizeof(buf), file1) != NULL && count < max_rows) {

    char *token = (strtok(buf, ",")); // first element of the first row
    char *float_buf;
    float fig = strtof(token, &float_buf); // converting token into a float
    features[count][0] = fig;              // storing it into our features array

    for (int i = 1; i < 4; i++) {
      token = strtok(NULL, ",");
      fig = strtof(token, &float_buf);
      features[count][i] = fig;
    }

    token = strtok(NULL, ",");
    int label = atoi(token);
    labels[count] = label;
    count++;
  }
  fclose(file1);
  return count;
}
