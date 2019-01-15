#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low == high) {
    return low;
  }
  //  if (low >= high) {
  // return high;
  // }
  if (f->invoke(high - 1) <= 0) {
    return high - 1;
  }
  else if (f->invoke(low) >= 0) {
    return low;
  }
  int mid;
  while (low <= high) {
    mid = low + (high - low) / 2;
    int ff = f->invoke(mid);
    if (ff == 0) {
      return mid;
    }
    else if (ff > 0) {
      high = mid - 1;
    }
    else {
      low = mid + 1;
    }
  }
  if (mid > high) {
    return mid - 1;
  }
  return mid;
}
/*
  if (f->invoke(high - 1) <= 0) {
    return high - 1;
  }
  if (f->invoke(low) >= 0) {
    return low;
  }
  if (low >= high - 1)
    return high;
  if (low == high - 1)
    return low;
  int mid = low + (high - low) / 2;
  int ff = f->invoke(mid);
  if (ff == 0)
    return mid;
  else if (ff > 0)
    return binarySearchForZero(f, low, mid);
  else
    return binarySearchForZero(f, mid + 1, high);
}
*/
