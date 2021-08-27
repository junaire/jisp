#ifndef JISP_INTERPRETER_H_
#define JISP_INTERPRETER_H_

#include "jisp/parser.h"
class Interpreter {
 public:
  Interpreter(ValuePtr vptr) : ast(std::move(vptr)) {}
  ValuePtr eval();

 private:
  ValuePtr ast;
};
#endif
