#include "election.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//include any other headers you need here...

state_t parseLine(const char * line) {
  state_t parse;
  parse.population = 0;
  parse.electoralVotes = 0;
  int i = 0;
  if (line == NULL) {  //check if point is  NULL
    printf("NULL");
    exit(EXIT_FAILURE);
  }
  if (*line < 'A' || *line > 'Z') {  //the first character of line should be capital letter
    printf("not capital");
    exit(EXIT_FAILURE);
  }

  const char * ptr = line;
  while (*line != '\0') {
    if (*line == ':') {  //count the number of ':'
      i++;
    }
    line++;
  }
  if (i != 2) {
    printf("not formal");
    exit(EXIT_FAILURE);
  }
  else {
    int j = 0;
    while (*ptr != ':') {  //read characters before the first':'
      if ((*ptr < 'A' && *ptr != 32) || (*ptr > 'Z' && *ptr < 'a') ||
          *ptr > 'z') {  //states' names only contain letter and space
        printf("not formal");
        exit(EXIT_FAILURE);
      }
      parse.name[j] = *ptr;
      j++;
      ptr++;
    }
    parse.name[j] = '\0';
    ptr++;
    char str[100];
    int n = 0;
    while (*ptr != ':') {              //read characters before the second ':'
      if (*ptr < '0' || *ptr > '9') {  //the population should be number
        printf("not formal");
        exit(EXIT_FAILURE);
      }
      else {
        str[n] = *ptr;
        ptr++;
      }
      n++;
    }
    str[n] = '\0';
    parse.population = atoi(str);  //transform the  stirngs into numbers
    ptr++;

    char str2[10];
    int m = 0;
    while (*ptr != '\0') {
      if (*ptr < '0' || *ptr > '9') {  // the number of votes should be number
        printf("not formal");
        exit(EXIT_FAILURE);
      }
      else {
        str2[m] = *ptr;
        ptr++;
        m++;
      }
      //STEP 1: write me
    }
    str2[m] = '\0';
    parse.electoralVotes = atoi(str2);
    return parse;
  }
}
unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  if (stateData == NULL || voteCounts == NULL || nStates == 0) {
    printf("wrong");
    return EXIT_FAILURE;
  }
  unsigned int votes = 0;
  for (size_t i = 0; i < nStates; i++) {
    if ((voteCounts[i] / stateData[i].population) < 0 ||
        voteCounts[i] / stateData[i].population > 1) {  //the percentage of votes should <=1 and >=0
      printf("wrong");
      return EXIT_FAILURE;
    }
    if (2 * voteCounts[i] /
        stateData[i].population) {  //Count the electoral votes if more than 50% of the votes
      votes = votes + stateData[i].electoralVotes;
    }
  }
  return votes;

  //STEP 2: write me
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  if (stateData == NULL || voteCounts == NULL || nStates == 0) {
    printf("wrong");
    return;
  }

  for (size_t i = 0; i < nStates; i++) {
    float percentage = ((float)(voteCounts[i]) / (float)(stateData[i].population));
    if (percentage <= 1 && percentage > 0) {  //the percentage of votes should <=1 and >=0
      if (percentage >= 0.495 &&
          percentage <=
              0.505) {  //recount if the percentage of votes is within +/-0.5% away from 50%.
        printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
               stateData[i].name,
               100 * percentage);
      }
    }
    //STEP 3: write me
    else {
      printf("wrong");
      return;
    }
  }
}
void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  if (stateData == NULL || voteCounts == NULL || nStates == 0) {
    printf("wrong");
    return;
  }

  float largest = 0.000;
  size_t s = 0;
  for (size_t i = 0; i < nStates; i++) {
    float percentage = ((float)(voteCounts[i]) / (float)(stateData[i].population));
    if (percentage <= 1 && percentage > 0) {
      if (largest < percentage) {  // find the largest of percentages
        largest = percentage;
        s = i;
      }
    }
    else {
      printf("wrong");
      return;
    }
  }
  if (largest > 1 || largest < 0 || s >= nStates) {  //the largest percentage should<=1 and >=0
    printf("wrong");
    return;
  }
  else {
    printf("Candidate A won %s with %.2f%% of the vote\n", stateData[s].name, 100 * largest);
  }
  //STEP 4: write me
}
