#ifndef JISP_FUNCTION_VALUE_H_
#define JISP_FUNCTION_VALUE_H_

#include <fmt/format.h>

#include <functional>
#include <iostream>
#include <utility>

#include "jisp/env.h"
#include "jisp/token.h"
#include "jisp/types.h"
#include "jisp/value.h"
using BuiltinFunction = std::function<ValuePtr(Env&, ValuePtr)>;

class FunctionValue final : public Value {
 public:
  explicit FunctionValue(BuiltinFunction fun)
      : Value(Types::FUNCTION), func(std::move(fun)) {}

  void inspect() override {
    std::cout << "<builtin function> in " << &func << "\n";
  }

  ValuePtr call(Env& env, ValuePtr vp) { return func(env, std::move(vp)); }

 private:
  BuiltinFunction func;
};
#endif
