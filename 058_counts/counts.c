#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  counts_t * count = malloc(sizeof(*count));
  count->array = NULL;
  count->array = malloc(sizeof(*(count->array)));
  count->unknowntimes = 0;
  count->size = 0;
  return count;
  //WRITE ME
}
void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->unknowntimes++;
  }
  else {
    int i = c->size;
    c->array = realloc(c->array, (i + 1) * sizeof(*(c->array)));
    c->array[i] = NULL;
    //    c->array[i] = malloc(sizeof(*(c->array[i])));
    int nn = 0;
    for (int j = 0; j < i; j++) {
      if (strcmp(c->array[j]->name, name) == 0) {
        c->array[j]->times++;
        break;
      }
      else {
        nn++;
      }
    }
    if (nn >= i) {
      c->array = realloc(c->array, (i + 1) * sizeof(*(c->array)));
      c->array[i] = malloc(sizeof(*(c->array[i])));
      c->array[i]->times = 0;
      c->array[i]->name = name;
      c->array[i]->times++;
      c->size++;
    }
    //WRITE ME
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  int j;
  for (j = 0; j < (c->size); j++) {
    fprintf(outFile, "%s : %d\n", c->array[j]->name, c->array[j]->times);
  }
  if (c->unknowntimes > 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unknowntimes);
  }

  //WRITE ME
}

void freeCounts(counts_t * c) {
  int i = c->size;
  for (int j = 0; j < i; j++) {
    free(c->array[j]);
  }
  free(c->array);
  free(c);

  //WRITE ME
}
