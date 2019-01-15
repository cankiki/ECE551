#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() {
  numElements = 0;
  data = NULL;
}
IntArray::IntArray(int n) {
  numElements = n;
  data = new int[n];
}

IntArray::IntArray(const IntArray & rhs) {
  data = new int[rhs.numElements];
  numElements = rhs.numElements;
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    int * temp = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {
      temp[i] = rhs.data[i];
    }
    delete[] data;
    numElements = rhs.numElements;
    data = temp;
  }
  return *this;
}
const int & IntArray::operator[](int index) const {
  assert(index < numElements);
  return data[index];
}
int & IntArray::operator[](int index) {
  assert(index < numElements);
  return data[index];
}
int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return false;
  }
  else {
    for (int i = 0; i < numElements; i++) {
      if (data[i] != rhs.data[i]) {
        return false;
      }
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (numElements == rhs.numElements) {
    return false;
  }
  else {
    for (int i = 0; i < numElements; i++) {
      if (data[i] == rhs.data[i]) {
        return false;
      }
    }
  }
  return true;
}
std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  if (rhs.size() <= 0) {
    s << "{}";
    return s;
  }
  else {
    s << "{";
    for (int i = 0; i < rhs.size() - 1; i++) {
      s << rhs.operator[](i) << ", ";
    }
    s << rhs.operator[](rhs.size() - 1);
    s << "}";
    return s;
  }
}
