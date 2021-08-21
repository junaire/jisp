#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include <memory>
#include <string>
#include <vector>
#include "types.h"

class Interpreter {
 public:
  explicit Interpreter(std::vector<std::unique_ptr<BaseValue>> ast) : ast(std::move(ast)) {}
  static std::vector<std::unique_ptr<BaseValue>> eval();
 private:
  std::vector<std::unique_ptr<BaseValue>> ast;
};
#endif
