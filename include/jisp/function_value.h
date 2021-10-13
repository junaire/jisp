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
  FunctionValue(std::string n, bool needLiteralArgs, BuiltinFunction fun)
      : func(std::move(fun)),
        name(std::move(n)),
        Value(ValueType::FUNCTION),
        needLiteralArgs(needLiteralArgs) {}

  std::string inspect() override { return getName(); }

  std::unique_ptr<Value> accept(ASTVisitor& visitor) override;

  std::unique_ptr<Value> call(Env& env, Value* vp) { return func(env, vp); }

  [[nodiscard]] bool isLiteral() const override { return true; }

  std::unique_ptr<Value> clone() override {
    return std::make_unique<FunctionValue>(name, needLiteralArgs, func);
  }
  [[nodiscard]] std::string getName() const { return name; }

  [[nodiscard]] bool isNeedLiteralArgs() const { return needLiteralArgs; }

 private:
  bool needLiteralArgs;
  std::string name;
  BuiltinFunction func;
};
#endif
