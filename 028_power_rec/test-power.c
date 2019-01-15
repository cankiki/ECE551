#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);
int run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (ans == expected_ans) {
    printf("right ");
    return 1;
  }
  else {
    printf("wrong ");
    return 0;
  }
}
//   which calls power, checks that the result is expected_ans, and
//if not, prints a message and calls exit(EXIT_FAILURE).

int main(void) {
  int a = run_check(0, 0, 1);
  int b = run_check(5, 0, 1);
  int c = run_check(0, 3, 0);
  int k = run_check(1, 1, 1);
  int m = run_check(-1, 2, 1);
  int n = run_check(429499295, 1, 429499295);
  if (a + b + c + k + m + n == 6) {
    return EXIT_SUCCESS;
  }
  else {
    return EXIT_FAILURE;
  }
}
