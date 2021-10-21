#include "jisp/ast_visitor.h"

#include <cassert>
#include <memory>

#include "jisp/error_value.h"
#include "jisp/function_value.h"
#include "jisp/lambda_value.h"
#include "jisp/number_value.h"
#include "jisp/sexpr_value.h"
#include "jisp/string_value.h"
#include "jisp/symbol_value.h"

std::unique_ptr<Value> ASTVisitor::visit(NumberValue* num) {
  return num->clone();
}

std::unique_ptr<Value> ASTVisitor::visit(StringValue* str) {
  return str->clone();
}

std::unique_ptr<Value> ASTVisitor::visit(FunctionValue* func) {
  return func->clone();
}

std::unique_ptr<Value> ASTVisitor::visit(SymbolValue* sym) {
  auto* val = enviroment->get(sym->getName());
  if (val == nullptr) {
    return sym->clone();
  }
  return val->clone();
}

std::unique_ptr<Value> ASTVisitor::visit(LambdaValue* lambda) {
  return lambda->clone();
}

std::unique_ptr<Value> ASTVisitor::visit(ErrorValue* error) {
  return error->clone();
}

std::unique_ptr<Value> ASTVisitor::visit(SexprValue* sexpr) {
  auto result = std::make_unique<SexprValue>();

  for (size_t i = 0; i < sexpr->size(); i++) {
    result->push(sexpr->at(i).accept(*this));
  }

  // FIXME: we shouldn't deal with LambdaValue here, need refactor
  if (result->at(0).isLambda()) {
    // FIXME: pop() makes someting frees formals and body
    auto* lam = result->at(0).toLambda();
    size_t size = 0;
    if (result->size() > 1) {
      size = result->size() - 1;
    }

    for (size_t i = 0; i < size; i++) {
      lam->setFormals(lam->getFormals()->at(i).toSymbol()->getName(),
                      result->pop(1));
    }
    return lam->eval();
  }

  if (result->at(0).isFunction()) {
    if (!result->at(0).toFunction()->isNeedLiteralArgs() ||
        result->isPartLiteral(1)) {
      auto fn = result->pop(0);
      return fn->toFunction()->call(*enviroment, result.release());
    }
  }

  if (result->size() == 1) {
    return result->pop(0);
  }

  return result;
}

