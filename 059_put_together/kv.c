#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
kvpair_t * sort(const char * line);
kvarray_t * readKVs(const char * fname) {
  if (fname == NULL) {
    return NULL;
    fprintf(stderr, "NULL");
  }

  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    return NULL;
    fprintf(stderr, "NULL");
  }
  kvarray_t * split = malloc(sizeof(*split));
  split->array = NULL;
  char * curr = NULL;
  size_t sz = 0;
  size_t i = 0;
  while ((getline(&curr, &sz, f)) >= 0) {
    split->array = realloc(split->array, (i + 1) * sizeof(*split->array));
    split->array[i] = sort(curr);
    free(curr);
    curr = NULL;
    i++;
  }
  free(curr);
  split->lengtht = i;
  if (fclose(f) != 0) {
    perror("Failed to close the file");
    return NULL;
  }
  return split;
}
kvpair_t * sort(const char * line) {
  kvpair_t * sort = malloc(sizeof(*sort));
  int lens1 = strchr(line, '=') - line;
  int lens2 = strchr(line, '\n') - strchr(line, '=');
  sort->key = malloc((lens1 + 1) * sizeof(char));
  sort->value = malloc(lens2 * sizeof(char));
  char * k = strchr(line, '=');
  strncpy(sort->key, line, lens1);
  sort->key[lens1] = '\0';
  strncpy(sort->value, k + 1, lens2 - 1);
  sort->value[lens2 - 1] = '\0';
  return sort;  //WRITE ME
}

void freeKVs(kvarray_t * pairs) {
  if (pairs == NULL) {
    fprintf(stderr, "NULL");
    exit(EXIT_FAILURE);
  }
  int i = pairs->lengtht;
  for (int j = 0; j < i; j++) {
    free(pairs->array[j]->key);
    free(pairs->array[j]->value);
    free(pairs->array[j]);
  }
  free(pairs->array);
  free(pairs);
  //WRITE ME
}

void printKVs(kvarray_t * pairs) {
  int i = pairs->lengtht;
  for (int j = 0; j < i; j++) {
    printf("key = '%s' value = '%s'\n", pairs->array[j]->key, pairs->array[j]->value);
  }
  //WRITE ME
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  if (pairs == NULL) {
    fprintf(stderr, "NULL");
    exit(EXIT_FAILURE);
  }
  int i = pairs->lengtht;
  int j = 0;
  while (j < i) {
    if (strcmp(pairs->array[j]->key, key) == 0) {
      break;
      //return pairs->array[j]->value;
    }
    if (strcmp(pairs->array[j]->key, key) != 0) {
      j++;
    }
  }
  if (j == i) {
    return NULL;
  }

  return pairs->array[j]->value;
  ;
  //WRITE ME
}
