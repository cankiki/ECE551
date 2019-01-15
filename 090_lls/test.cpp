#include <cassert>
#include <cstdlib>

#include "ll.h"
void testList() {
  LinkedList<int> a;
  a.addBack(3);
  assert(a.find(-9) == -1);
  a.addBack(4);
  assert(a.tail->data == 4);
  assert(a.getSize() == 2);
  a.addFront(5);
  assert(a.head->prev == NULL);
  assert(a.getSize() == 3);
  LinkedList<int> b;
  b = a;
  assert(b.getSize() == 3);
  assert(b[1] == 3);
  assert(b.head->data == a.head->data && b.tail->data == a.tail->data);
  assert(b.head != a.head && b.tail != a.tail);
  LinkedList<int> c(a);
  assert(c.head->data == a.head->data && c.tail->data == a.tail->data);
  assert(c.getSize() == 3);
  assert(c[1] == 3);
  assert(c.head != a.head && c.tail != a.tail);
  a.addFront(5);
  assert(a.remove(5) == 1 && a.find(5) == 0);
  assert(a.remove(7) == 0);
  assert(a.getSize() == 3);
  a.remove(2);
  a.remove(3);
  assert(a.head->next->data == 4 && a.tail->prev->data == 5);
  assert(a.getSize() == 2);
  assert(a.find(9) == -1);
  LinkedList<int> m;
  m.addFront(1);
  m.addBack(2);
  m.addBack(4);
  m.addBack(5);
  m.remove(1);
  assert(m.head->data == 2 && m.head->prev == NULL);
  m.remove(5);
  assert(m.tail->data == 4 && m.tail->next == NULL && m.head->next->next == NULL);
}
int main(void) {
  testList();
  return EXIT_SUCCESS;
}
