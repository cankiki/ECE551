#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high);
class CountedIntFn : public Function<int, int>
{
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};
void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  int n = (high > low) ? (log(high - low) / log(2) + 1) : 1;
  CountedIntFn * fn = new CountedIntFn(n, f, mesg);
  int ans = binarySearchForZero(fn, low, high);
  if (ans != expected_ans) {
    std::cerr << mesg;
    exit(EXIT_FAILURE);
  }
}

class easyFunction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return arg; }
};
int main() {
  Function<int, int> * f = new easyFunction;
  check(f, -2, 0, -1, "wonrg 1");
  check(f, -100, -1, -2, "wrong 2");
  check(f, 0, 0, 0, "wrong 3");
  check(f, 2, 6, 2, "wrong 4");
  check(f, -9999999, 0, -1, "wrong 5");
  check(f, -1, -1, -1, "wrong 6");
  check(f, 0, 1, 0, "wrong 7");
  check(f, -2, 4, 0, "wrong 8");
}
