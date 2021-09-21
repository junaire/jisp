#include "jisp/builtin.h"

#include "jisp/number_value.h"
#include "jisp/sexpr_value.h"

ValuePtr builtinOperators(Env& env, const ValuePtr& vp, const char* op) {
  auto sexpr = std::dynamic_pointer_cast<SexprValue>(vp);
  int result =
      std::dynamic_pointer_cast<NumberValue>(sexpr->pop(0))->getValue();
  if (strcmp(op, "+") == 0) {
    for (int i = 0; i < sexpr->size(); i++) {
      result += std::dynamic_pointer_cast<NumberValue>((*sexpr)[i])->getValue();
    }
  }

  if (strcmp(op, "-") == 0) {
    for (int i = 0; i < sexpr->size(); i++) {
      result -= std::dynamic_pointer_cast<NumberValue>((*sexpr)[i])->getValue();
    }
  }

  if (strcmp(op, "*") == 0) {
    for (int i = 0; i < sexpr->size(); i++) {
      result *= std::dynamic_pointer_cast<NumberValue>((*sexpr)[i])->getValue();
    }
  }

  if (strcmp(op, "/") == 0) {
    // TODO(Jun): throw an error when dividend is 0
    for (int i = 0; i < sexpr->size(); i++) {
      result /= std::dynamic_pointer_cast<NumberValue>((*sexpr)[i])->getValue();
    }
  }
  return std::make_shared<NumberValue>(result);
}

ValuePtr builtinPrint(Env& env, const ValuePtr& vp) {
  auto sexpr = std::dynamic_pointer_cast<SexprValue>(vp);
  sexpr->inspect();
  return std::make_shared<SexprValue>(Types::SEXPR);
}

ValuePtr add_builtin(const BuiltinFunction& func) {
  return std::make_shared<FunctionValue>(func);
}

void add_builtins(Env& env) {
  env.set("+", add_builtin([](Env& env, const ValuePtr& vp) {
            return builtinOperators(env, vp, "+");
          }));
  env.set("-", add_builtin([](Env& env, const ValuePtr& vp) {
            return builtinOperators(env, vp, "-");
          }));
  env.set("*", add_builtin([](Env& env, const ValuePtr& vp) {
            return builtinOperators(env, vp, "*");
          }));
  env.set("/", add_builtin([](Env& env, const ValuePtr& vp) {
            return builtinOperators(env, vp, "/");
          }));

  env.set("print", add_builtin([](Env& env, const ValuePtr& vp) {
            return builtinPrint(env, vp);
          }));
}
