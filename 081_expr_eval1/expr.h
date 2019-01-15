#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;
class Expression
{
 public:
  virtual std::string toString() const = 0;

  virtual ~Expression() {}
};
class NumExpression : public Expression
{
 private:
  long num;

 public:
  NumExpression(long n) : num(n) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << num;
    return ss.str();
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression
{
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}

  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << "+" << rhs->toString() << ")";
    return ss.str();
  }

  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};
