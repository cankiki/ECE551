#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  char matrix[10][10];
  char str[12];
  int i = 0;
  while (fgets(str, 12, f) != NULL) {
    while (i == 10) {
      fprintf(stderr, "too many lines");
      return EXIT_FAILURE;
    }
    if (strchr(str, '\n') == NULL) {
      fprintf(stderr, "line is too long\n");
      return EXIT_FAILURE;
    }
    if (strlen(str) != 11) {
      fprintf(stderr, "too short\n");
      return EXIT_FAILURE;
    }
    for (int j = 0; j < 10; j++) {
      matrix[i][j] = str[j];
    }
    i++;
  }
  if (i != 10) {
    fprintf(stderr, "not enough lines");
    return EXIT_FAILURE;
  }
  char ma2[10][10];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      ma2[i][j] = matrix[10 - j - 1][i];
      fprintf(stdout, "%c", ma2[i][j]);
    }
    fprintf(stdout, "\n");
  }

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
