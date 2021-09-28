#ifndef JISP_FUNCTION_VALUE_H_
#define JISP_FUNCTION_VALUE_H_

#include <fmt/format.h>

#include <functional>
#include <utility>

#include "jisp/env.h"
#include "jisp/token.h"
#include "jisp/value.h"

using BuiltinFunction = std::function<std::unique_ptr<Value>(Env&, Value*)>;

class FunctionValue : public Value {
 public:
  explicit FunctionValue(BuiltinFunction fun) : func(std::move(fun)) {}

  std::string inspect() override {
    return fmt::format("<builtin function> in {}\n", fmt::ptr(&func));
  }

  std::unique_ptr<Value> accept(ASTVisitor& visitor) override;

  std::unique_ptr<Value> call(Env& env, Value* vp) { return func(env, vp); }

  BuiltinFunction get() { return func; }

 private:
  BuiltinFunction func;
};
#endif
