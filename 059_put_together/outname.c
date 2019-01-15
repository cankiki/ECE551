#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  if (inputName == NULL) {
    return NULL;
  }
  char * name = malloc((strlen(inputName) + 8) * sizeof(char));
  unsigned long i;
  for (i = 0; i < strlen(inputName); i++) {
    name[i] = inputName[i];
  }
  name[i] = '\0';
  strcat(name, ".counts");
  return name;
  //WRITE ME
}
