#include "jisp/builtin.h"

#include "jisp/function_value.h"
#include "jisp/number_value.h"
#include "jisp/sexpr_value.h"
#include "jisp/symbol_value.h"

std::unique_ptr<Value> builtinOperators(Env& env, Value* vp, const char* op) {
  auto* sexpr = vp->toSexpr();
  int result = sexpr->pop(0)->toNumber()->getValue();
  if (strcmp(op, "+") == 0) {
    for (int i = 0; i < sexpr->size(); i++) {
      result += sexpr->at(i)->toNumber()->getValue();
    }
  }

  if (strcmp(op, "-") == 0) {
    for (int i = 0; i < sexpr->size(); i++) {
      result -= sexpr->at(i)->toNumber()->getValue();
    }
  }

  if (strcmp(op, "*") == 0) {
    for (int i = 0; i < sexpr->size(); i++) {
      result *= sexpr->at(i)->toNumber()->getValue();
    }
  }

  if (strcmp(op, "/") == 0) {
    // TODO(Jun): throw an error when dividend is 0
    for (int i = 0; i < sexpr->size(); i++) {
      result /= sexpr->at(i)->toNumber()->getValue();
    }
  }
  return std::make_unique<NumberValue>(result);
}

std::unique_ptr<Value> builtinPrint(Env& env, Value* vp) {
  auto* sexpr = vp->toSexpr();
  sexpr->inspect();
  return std::make_unique<SexprValue>();
}

std::unique_ptr<Value> builtinDefine(Env& env, Value* vp) {
  auto* sexpr = vp->toSexpr();
  env.set(sexpr->at(0)->toSymbol()->getName(), std::move(sexpr->get(1)));
  return std::make_unique<SexprValue>();
}
