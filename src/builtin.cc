#include "jisp/builtin.h"

#include <iostream>

#include "jisp/error_value.h"
#include "jisp/function_value.h"
#include "jisp/lambda_value.h"
#include "jisp/number_value.h"
#include "jisp/sexpr_value.h"
#include "jisp/symbol_value.h"

std::unique_ptr<Value> builtinOperators(Env& env, Value* vp, const char* op) {
  auto* sexpr = vp->toSexpr();
  int result = 0;
  if (strcmp(op, "+") == 0) {
    result = sexpr->pop(0)->toNumber()->getValue();
    for (int i = 0; i < sexpr->size(); i++) {
      result += sexpr->at(i)->toNumber()->getValue();
    }
  }

  if (strcmp(op, "-") == 0) {
    result = sexpr->pop(0)->toNumber()->getValue();
    for (int i = 0; i < sexpr->size(); i++) {
      result -= sexpr->at(i)->toNumber()->getValue();
    }
  }

  if (strcmp(op, "*") == 0) {
    result = sexpr->pop(0)->toNumber()->getValue();
    for (int i = 0; i < sexpr->size(); i++) {
      result *= sexpr->at(i)->toNumber()->getValue();
    }
  }

  if (strcmp(op, "/") == 0) {
    result = sexpr->pop(0)->toNumber()->getValue();
    if (result == 0) {
      return std::make_unique<ErrorValue>("Dividend can not be zero");
    }
    for (int i = 0; i < sexpr->size(); i++) {
      result /= sexpr->at(i)->toNumber()->getValue();
    }
  }
  return std::make_unique<NumberValue>(result);
}

std::unique_ptr<Value> builtinCompare(Env& env, Value* vp, const char* op) {
  auto* sexpr = vp->toSexpr();
  if (strcmp(op, "==") == 0) {
    return std::make_unique<NumberValue>(1);
  }
  if (strcmp(op, "!=") == 0) {
    return std::make_unique<NumberValue>(0);
  }
  return nullptr;
}

std::unique_ptr<Value> builtinPrint(Env& env, Value* vp) {
  if (vp->toSexpr()->size() == 1) {
    std::cout << vp->toSexpr()->at(0)->inspect() << "\n";
  }
  return std::make_unique<SexprValue>();
}

std::unique_ptr<Value> builtinDefine(Env& env, Value* vp) {
  auto* sexpr = vp->toSexpr();
  env.set(sexpr->at(0)->toSymbol()->getName(), std::move(sexpr->get(1)));
  return std::make_unique<SexprValue>();
}

std::unique_ptr<Value> builtinLambda(Env& env, Value* vp) {
  auto* sexpr = vp->toSexpr();

  auto formals = sexpr->pop(0);
  auto body = sexpr->pop(0);

  return std::make_unique<LambdaValue>(std::move(formals), std::move(body),
                                       &env);
}

std::unique_ptr<Value> addBuiltin(const std::string& name, bool isNeedLiteral,
                                  auto&& func) {
  return std::make_unique<FunctionValue>(name, isNeedLiteral, func);
}

void initBuiltins(Env& env) {
  /*
addBuiltin("+", true, [](Env& env, Value* vp) {
return builtinOperators(env, vp, "+");
});
addBuiltin("-", true, [](Env& env, Value* vp) {
return builtinOperators(env, vp, "-");
});
addBuiltin("*", true, [](Env& env, Value* vp) {
return builtinOperators(env, vp, "*");
});
addBuiltin("/", true, [](Env& env, Value* vp) {
return builtinOperators(env, vp, "/");
});
*/

  env.set("lambda", addBuiltin("lambda", false, [](Env& env, Value* vp) {
            return builtinLambda(env, vp);
          }));
  env.set("define", addBuiltin("define", false, [](Env& env, Value* vp) {
            return builtinDefine(env, vp);
          }));
  env.set("print", addBuiltin("print", true, [](Env& env, Value* vp) {
            return builtinPrint(env, vp);
          }));
}
