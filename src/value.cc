#include "jisp/ast_visitor.h"
#include "jisp/function_value.h"
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

NumberValue* Value::toNumber() { return dynamic_cast<NumberValue*>(this); }

StringValue* Value::toString() { return dynamic_cast<StringValue*>(this); }

SymbolValue* Value::toSymbol() { return dynamic_cast<SymbolValue*>(this); }

SexprValue* Value::toSexpr() { return dynamic_cast<SexprValue*>(this); }

FunctionValue* Value::toFunction() {
  return dynamic_cast<FunctionValue*>(this);
}

