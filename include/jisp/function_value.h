#ifndef JISP_FUNCTION_VALUE_H_
#define JISP_FUNCTION_VALUE_H_

#include <fmt/format.h>

#include <functional>
#include <string>
#include <utility>

#include "jisp/env.h"
#include "jisp/token.h"
#include "jisp/types.h"
#include "jisp/value.h"

using BuiltinFunction = std::function<std::unique_ptr<Value>(Env&, Value*)>;

class FunctionValue final : public Value {
 public:
  FunctionValue(std::string n, BuiltinFunction fun)
      : func(std::move(fun)), name(std::move(n)), Value(ValueType::FUNCTION) {}

  std::string inspect() override {
    return fmt::format("<builtin function> in {}\n", fmt::ptr(&func));
  }

  std::unique_ptr<Value> accept(ASTVisitor& visitor) override;

  std::unique_ptr<Value> call(Env& env, Value* vp) { return func(env, vp); }

  BuiltinFunction get() { return func; }

  [[nodiscard]] std::string getName() const { return name; }

 private:
  std::string name;
  BuiltinFunction func;
};
#endif
