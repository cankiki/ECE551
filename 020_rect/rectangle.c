#include <stdio.h>
#include <stdlib.h>

// I've provided "min" and "max" functions in case they are useful
// to you
int min(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}
int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

struct rectangle_tag {
  int x;
  int y;
  int width;
  int height;
};
typedef struct rectangle_tag rectangle_t;  // Declare your rectangle structure here!

rectangle_t canonicalize(rectangle_t r) {
  if (r.width < 0) {
    r.x = r.x + r.width;
    r.width = -r.width;
  }
  if (r.height < 0) {
    r.y = r.y + r.height;
    r.height = -r.height;
  }

  // WRITE THIS FUNCTION
  return r;
}
rectangle_t intersection(rectangle_t r1, rectangle_t r2) {
  r1 = canonicalize(r1);
  r2 = canonicalize(r2);
  int i = r1.x + r1.width;
  int j = r2.x + r2.width;
  int m = r1.y + r1.height;
  int n = r2.y + r2.height;
  int z;
  int q;

  r1.x = max(r1.x, r2.x);
  r1.y = max(r1.y, r2.y);
  z = min(i, j);
  q = min(m, n);
  r1.width = z - r1.x;
  r1.height = q - r1.y;
  // WRITE THIS FUNCTION
  if (((r1.x + r1.width) >= r1.x && (r1.y + r1.height) >= r1.y)) {
    return r1;
  }
  else {
    r1.width = 0;
    r1.height = 0;
    return r1;
  }
}
// You should not need to modify any code below this line
void printRectangle(rectangle_t r) {
  r = canonicalize(r);
  if (r.width == 0 && r.height == 0) {
    printf("<empty>\n");
  }
  else {
    printf("(%d,%d) to (%d,%d)\n", r.x, r.y, r.x + r.width, r.y + r.height);
  }
}

int main(void) {
  rectangle_t r1;
  rectangle_t r2;
  rectangle_t r3;
  rectangle_t r4;

  r1.x = 2;
  r1.y = 3;
  r1.width = 5;
  r1.height = 6;
  printf("r1 is ");
  printRectangle(r1);

  r2.x = 4;
  r2.y = 5;
  r2.width = -5;
  r2.height = -7;
  printf("r2 is ");
  printRectangle(r2);

  r3.x = -2;
  r3.y = 7;
  r3.width = 7;
  r3.height = -10;
  printf("r3 is ");
  printRectangle(r3);

  r4.x = 0;
  r4.y = 7;
  r4.width = -4;
  r4.height = 2;
  printf("r4 is ");
  printRectangle(r4);

  // test everything with r1
  rectangle_t i = intersection(r1, r1);
  printf("intersection(r1, r1): ");
  printRectangle(i);

  i = intersection(r1, r2);
  printf("intersection(r1, r2): ");
  printRectangle(i);

  i = intersection(r1, r3);
  printf("intersection(r1, r3): ");
  printRectangle(i);

  i = intersection(r1, r4);
  printf("intersection(r1, r4): ");
  printRectangle(i);

  // test everything with r2
  i = intersection(r2, r1);
  printf("intersection(r2, r1): ");
  printRectangle(i);

  i = intersection(r2, r2);
  printf("intersection(r2, r2): ");
  printRectangle(i);

  i = intersection(r2, r3);
  printf("intersection(r2, r3): ");
  printRectangle(i);

  i = intersection(r2, r4);
  printf("intersection(r2, r4): ");
  printRectangle(i);

  // test everything with r3
  i = intersection(r3, r1);
  printf("intersection(r3, r1): ");
  printRectangle(i);

  i = intersection(r3, r2);
  printf("intersection(r3, r2): ");
  printRectangle(i);

  i = intersection(r3, r3);
  printf("intersection(r3, r3): ");
  printRectangle(i);

  i = intersection(r3, r4);
  printf("intersection(r3, r4): ");
  printRectangle(i);

  // test everything with r4
  i = intersection(r4, r1);
  printf("intersection(r4, r1): ");
  printRectangle(i);

  i = intersection(r4, r2);
  printf("intersection(r4, r2): ");
  printRectangle(i);

  i = intersection(r4, r3);
  printf("intersection(r4, r3): ");
  printRectangle(i);

  i = intersection(r4, r4);
  printf("intersection(r4, r4): ");
  printRectangle(i);

  return EXIT_SUCCESS;
}
