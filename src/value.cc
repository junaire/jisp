#include "jisp/ast_visitor.h"
#include "jisp/error_value.h"
#include "jisp/function_value.h"
#include "jisp/lambda_value.h"
#include "jisp/number_value.h"
#include "jisp/sexpr_value.h"
#include "jisp/string_value.h"
#include "jisp/symbol_value.h"

std::unique_ptr<Value> NumberValue::accept(ASTVisitor& visitor) {
  return visitor.visit(this);
}

std::unique_ptr<Value> StringValue::accept(ASTVisitor& visitor) {
  return visitor.visit(this);
}

std::unique_ptr<Value> SymbolValue::accept(ASTVisitor& visitor) {
  return visitor.visit(this);
}

std::unique_ptr<Value> SexprValue::accept(ASTVisitor& visitor) {
  return visitor.visit(this);
}

std::unique_ptr<Value> FunctionValue::accept(ASTVisitor& visitor) {
  return visitor.visit(this);
}

std::unique_ptr<Value> LambdaValue::accept(ASTVisitor& visitor) {
  return visitor.visit(this);
}

std::unique_ptr<Value> ErrorValue::accept(ASTVisitor& visitor) {
  return visitor.visit(this);
}

NumberValue* Value::toNumber() { return dynamic_cast<NumberValue*>(this); }

StringValue* Value::toString() { return dynamic_cast<StringValue*>(this); }

SymbolValue* Value::toSymbol() { return dynamic_cast<SymbolValue*>(this); }

SexprValue* Value::toSexpr() { return dynamic_cast<SexprValue*>(this); }

LambdaValue* Value::toLambda() { return dynamic_cast<LambdaValue*>(this); }

FunctionValue* Value::toFunction() {
  return dynamic_cast<FunctionValue*>(this);
}

ErrorValue* Value::toError() { return dynamic_cast<ErrorValue*>(this); }

std::unique_ptr<Value> LambdaValue::eval() {
  // FIXME: env can be shared
  ASTVisitor visitor(std::move(env));
  return visitor.visit(getBody());
}

