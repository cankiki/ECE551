#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int breaker(FILE * f) {
  int c;
  int array[26] = {0};
  int max = 0;
  int key = 0;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      array[c - 'a']++;
    }
  }
  for (int i = 0; i < 26; i++) {
    if (array[i] > array[max]) {
      max = i;
    }
  }

  max = max + 'a';
  if (max < 'e') {
    key = (max - 'e') + 26;
  }
  else {
    key = max - 'e';
  }
  return key;
}

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
  int key = breaker(f);
  if (key >= 0 && key < 26) {
    fprintf(stdout, "%d\n", key);
  }
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
