#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  if (filename == NULL) {
    return NULL;
    fprintf(stderr, "NULL");
  }

  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    return NULL;
    fprintf(stderr, "NULL");
  }
  counts_t * countfile = createCounts();
  char ** lines = NULL;
  char * curr = NULL;
  size_t sz = 0;
  size_t i = 0;
  while ((getline(&curr, &sz, f)) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));

    char * ptr = strchr(curr, '\n');
    *ptr = '\0';

    //lines = realloc(lines, (i + 1) * sizeof(*lines));
    //lines[i] = curr;
    //char * ptr = lines[i];
    //ptr = strchr(lines[i], '\n');
    //*ptr = '\0';
    lines[i] = lookupValue(kvPairs, curr);
    addCount(countfile, lines[i]);
    free(curr);
    curr = NULL;
    i++;
  }
  free(curr);
  free(lines);
  if (fclose(f) != 0) {
    perror("Failed to close the file");
    return NULL;
  }
  return countfile;
}

int main(int argc, char ** argv) {
  if (argc <= 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  //WRITE ME (plus add appropriate error checking!)
  kvarray_t * kv = readKVs(
      argv[1]);  //read the key/value pairs from the file named by argv[1] (call the result kv)
  int i;
  for (i = 2; i < argc; i++) {  //count from 2 to argc (call the number you count i)
    counts_t * c = countFile(
        argv[i],
        kv);  //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    char * outName = computeOutputFileName(argv[i]);
    //compute the output file name from argv[i] (call this outName)
    if (outName == NULL) {
      fprintf(stderr, "NULL");
    }
    FILE * f = fopen(outName, "w");
    //open the file named by outName (call that f)
    printCounts(c, f);
    //print the counts from c into the FILE f
    if (fclose(f) != 0) {
      perror("Failed to close the input file!");
      return EXIT_FAILURE;
    }
    //close f
    free(outName);
    freeCounts(c);
  }
  freeKVs(kv);
  //free the memory for outName and c

  //free the memory for kv

  return EXIT_SUCCESS;
}
