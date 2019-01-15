#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n) {
  size_t m = 1;
  size_t x = 1;
  if (n <= 1) {
    return n;
  }

  for (size_t i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {
      m++;
    }
    else {
      if (x < m) {
        x = m;
      }
      m = 1;
    }
  }
  if (m > x) {
    return m;
  }
  else {
    return x;
  }
}
