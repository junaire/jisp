#include "jisp/ast_visitor.h"

#include <memory>

#include "jisp/function_value.h"
#include "jisp/number_value.h"
#include "jisp/sexpr_value.h"
#include "jisp/string_value.h"
#include "jisp/symbol_value.h"

std::unique_ptr<Value> ASTVisitor::visit(NumberValue* num) {
  return std::make_unique<NumberValue>(num->getValue());
}

std::unique_ptr<Value> ASTVisitor::visit(StringValue* str) {
  return std::make_unique<StringValue>(str->getValue());
}

std::unique_ptr<Value> ASTVisitor::visit(FunctionValue* func) {
  return std::make_unique<FunctionValue>(func->get());
}

std::unique_ptr<Value> ASTVisitor::visit(SymbolValue* sym) {
  auto* val = enviroment->get(sym->getName());
  if (!val) {
    return std::make_unique<SymbolValue>(sym->getName(), nullptr);
  }
  if (val->isNumber()) {
    return std::make_unique<NumberValue>(val->toNumber()->getValue());
  }
  if (val->isString()) {
    return std::make_unique<StringValue>(val->toString()->getValue());
  }
  if (val->isFunction()) {
    return std::make_unique<FunctionValue>(val->toFunction()->get());
  }
  if (val->isSexpr()) {
    auto res = std::make_unique<SexprValue>();
    while (val->toSexpr()->size() != 0) {
      res->push(val->toSexpr()->pop(0));
    }
    return res;
  }
}

std::unique_ptr<Value> ASTVisitor::visit(SexprValue* sexpr) {
  // eval all nodes
  // replace previous nodes
  for (size_t i = 0; i < sexpr->size(); i++) {
    sexpr->get(i) = sexpr->at(i)->accept(*this);
  }

  // TODO(Jun): sexpr size is 0 or 1

  // Is this works???
  auto* f = sexpr->pop(0)->toFunction();

  return f->call(*enviroment, sexpr);
}
