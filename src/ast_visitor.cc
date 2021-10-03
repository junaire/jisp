#include "jisp/ast_visitor.h"

#include <iostream>
#include <memory>

#include "jisp/function_value.h"
#include "jisp/lambda_value.h"
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
  return std::make_unique<FunctionValue>(func->getName(), func->get());
}

std::unique_ptr<Value> ASTVisitor::visit(SymbolValue* sym) {
  auto* val = enviroment->get(sym->getName());
  if (val == nullptr) {
    return std::make_unique<SymbolValue>(sym->getName(), nullptr);
  }
  if (val->isNumber()) {
    return std::make_unique<NumberValue>(val->toNumber()->getValue());
  }
  if (val->isString()) {
    return std::make_unique<StringValue>(val->toString()->getValue());
  }
  if (val->isFunction()) {
    return std::make_unique<FunctionValue>(val->toFunction()->getName(),
                                           val->toFunction()->get());
  }
  if (val->isLambda()){
    return std::make_unique<LambdaValue>(val->toLambda()->moveFormals(), val->toLambda()->moveBody(), enviroment.get());
  }
  if (val->isSexpr()) {
    auto res = std::make_unique<SexprValue>();
    while (val->toSexpr()->size() != 0) {
      res->push(val->toSexpr()->pop(0));
    }
    return res;
  }
  return nullptr;
}

std::unique_ptr<Value> ASTVisitor::visit(LambdaValue* sexpr) {
  std::cout << "I'm a loser in lambda... :-(\n";
  return nullptr;
}

std::unique_ptr<Value> ASTVisitor::visit(SexprValue* sexpr) {
  auto result = std::make_unique<SexprValue>();

  for (size_t i = 0; i < sexpr->size(); i++) {
    result->push(sexpr->at(i)->accept(*this));
  }



  // FIXME: we shouldn't deal with LambdaValue here, need refactor
  if (result->at(0)->isLambda()) {
    std::cout << result->size() << "\n";
    std::cout << result->at(1)->toNumber()->getValue() << "\n";
    auto* lam = result->pop(0)->toLambda();
    auto* formals = lam->getFormals();
    auto size = result->size();

    for (size_t i = 0; i < size; i++) {
      lam->setFormals(formals->get(i)->toSymbol()->getName(), result->pop(0));
    }

    return visit(lam->getBody());
  }

  //if (sexpr->size() == 1) {
   // result->push(sexpr->pop(0));
    //return result;
  //}
  auto* f = result->at(0);

  // We shouldn't try to call this, as it is function body.
  // We need to figure out how to smartly omit this...

  // When call PLUS, error occured..., as we don't know symbols in the function
  // body.....
  if (f->isFunction()) {
    auto fn = result->pop(0);
    return fn->toFunction()->call(*enviroment, result.get());
  }

  return result;
}

