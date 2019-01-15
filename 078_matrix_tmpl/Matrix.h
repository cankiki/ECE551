#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
template<typename T>
class Matrix
{
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() {
    numRows = 0;
    numColumns = 0;
  }
  Matrix(int r, int c) {
    numRows = r;
    numColumns = c;
    if (r > 0 && c >= 0) {
      rows.resize(r);
      for (int i = 0; i < r; i++) {
        rows[i].resize(c);
      }
    }
  }

  Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
    /* for (int i = 0; i < rhs.numRows; i++) { */
    rows = rhs.rows;
  }

  ~Matrix() { rows.clear(); }

  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      /* if (rhs.numRows == 0) {
        rows = NULL;
        numRows = rhs.numRows;
        numColumns = rhs.numColumns;
      }
      */
      vector<std::vector<T> > temp(rhs.rows);
      /*      for (int i = 0; i < rhs.numRows; i++) {
        for (int j = 0; j < rhs.numColumns; j++) {
          temp[i][j] = rhs[i][j];
        }
      }
      */
      this->~Matrix();
      numColumns = rhs.numColumns;
      numRows = rhs.numRows;
      rows = temp;
    }

    return *this;
  }

  int getRows() const { return numRows; }

  int getColumns() const { return numColumns; }

  const vector<T> & operator[](int index) const {
    assert(index < numRows && index >= 0);
    return rows[index];
  }

  vector<T> & operator[](int index) {
    assert(index < numRows && index >= 0);
    return rows[index];
  }
  bool operator==(const Matrix & rhs) const {
    if (numColumns != rhs.numColumns || numRows != rhs.numRows) {
      return false;
    }
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        if ((*this)[i][j] != rhs[i][j]) {
          return false;
        }
      }
    }

    return true;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert(numRows == rhs.numRows);
    assert(numColumns == rhs.numColumns);
    Matrix a(rhs.numRows, rhs.numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        a[i][j] = (*this)[i][j] + rhs[i][j];
      }
    }
    return a;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() == 0) {
    s << "[  ]";
    return s;
  }
  else if (rhs.getRows() != 0 && rhs.getColumns() == 0) {
    s << "[ ";
    for (int i = 0; i < rhs.getRows(); i++) {
      if (i == rhs.getRows() - 1) {
        s << "{} ]";
        break;
      }
      s << "{},\n";
    }
    return s;
  }

  s << "[ ";
  for (int i = 0; i < rhs.getRows() - 1; i++) {
    s << "{";

    for (int j = 0; j < rhs.getColumns(); j++) {
      if (j == rhs.getColumns() - 1) {
        s << rhs[i][j] << "},\n";
        break;
      }
      s << rhs[i][j] << ", ";
    }
  }
  s << "{";
  for (int j = 0; j < rhs.getColumns(); j++) {
    if (j == rhs.getColumns() - 1) {
      s << rhs[rhs.getRows() - 1][j] << "} ]";
      break;
    }
    s << rhs[rhs.getRows() - 1][j] << ", ";
  }
  return s;
}
/*    for (int i = 0; i < rhs.getRows() - 1; i++) {
      s << "{},\n";
    }
    s << "{}"
      << " ]";
    return s;
  }
  else {
    s << "[ ";
    for (int i = 0; i < rhs.getRows() - 1; i++) {
      for (int j = 0; j < rhs.getColumns() - 1; j++) {
        s << rhs[i][j];
      }
    }
    s << ",\n";
    s << rhs[rhs.getRows() - 1][rhs.getColumns() - 1] << " ]";
    return s;
  }
}
*/
//YOUR CODE GOES HERE!

#endif
