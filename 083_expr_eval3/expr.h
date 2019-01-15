#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;
class Expression
{
 public:
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
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
  virtual long evaluate() const { return num; }
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
  virtual long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }
  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};

class MinusExpression : public Expression
{
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}

  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << "-" << rhs->toString() << ")";
    return ss.str();
  }
  virtual long evaluate() const { return lhs->evaluate() - rhs->evaluate(); }
  virtual ~MinusExpression() {
    delete lhs;
    delete rhs;
  }
};

class TimesExpression : public Expression
{
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}

  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << "*" << rhs->toString() << ")";
    return ss.str();
  }
  virtual long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }
  virtual ~TimesExpression() {
    delete lhs;
    delete rhs;
  }
};
class DivExpression : public Expression
{
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  DivExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}

  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << "/" << rhs->toString() << ")";
    return ss.str();
  }
  virtual long evaluate() const { return lhs->evaluate() / rhs->evaluate(); }
  virtual ~DivExpression() {
    delete lhs;
    delete rhs;
  }
};
