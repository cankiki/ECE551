// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>
int sumSeq2(int low, int high);
int seq2(int x) {
  int seq2x = x * (x + 3) + 1;
  return seq2x;
}
int main(void) {
  int n1 = -4;
  int m1 = 5;
  int seq = seq2(n1);
  printf("seq2(%d) = %d\n", n1, seq);
  if (seq == m1) {
    printf("right\n ");
  }
  else {
    printf("wrong\n ");
  }

  n1 = 0;
  m1 = 1;
  seq = seq2(n1);
  printf("seq2(%d) = %d\n", n1, seq);
  if (seq == m1) {
    printf("right\n ");
  }
  else {
    printf("wrong\n ");
  }

  n1 = 5;
  m1 = 41;
  seq = seq2(n1);
  printf("seq2(%d) = %d\n", n1, seq);
  if (seq == m1) {
    printf("right\n ");
  }
  else {
    printf("wrong\n ");
  }
  int low = 0, high = 2;
  int z = sumSeq2(low, high);
  printf("sumSeq2(%d, %d) = %d\n", low, high, z);

  low = 1;
  high = 1;
  z = sumSeq2(low, high);
  printf("sumSeq2(%d, %d) = %d\n", low, high, z);

  low = 3;
  high = 6;
  z = sumSeq2(low, high);
  printf("sumSeq2(%d, %d) = %d\n", low, high, z);

  low = 9;
  high = 7;
  z = sumSeq2(low, high);
  printf("sumSeq2(%d, %d) = %d\n", low, high, z);

  return EXIT_SUCCESS;
}
int sumSeq2(int low, int high) {
  int sum = 0;
  if (low >= high) {
    return 0;
  }
  else {
    for (int i = low; i >= low && i < high; i++) {
      int seq = seq2(i);
      sum = sum + seq;
    }
    return sum;
  }
}
