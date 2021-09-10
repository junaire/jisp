#ifndef JISP_INTERPRETER_H_
#define JISP_INTERPRETER_H_

#include <utility>

#include "jisp/env.h"
#include "jisp/parser.h"

class Interpreter {
 public:
  explicit Interpreter(ValuePtr vptr) : ast(std::move(vptr)) {}
  Interpreter(ValuePtr vptr, Env& env) : ast(std::move(vptr)), environment(env) {}
  ValuePtr eval();

 private:
  ValuePtr evalSexpr(const ValuePtr& node);
  ValuePtr evalNode(ValuePtr node);
  ValuePtr ast;
  Env environment;
};
#endif
