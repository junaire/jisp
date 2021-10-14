#ifndef JISP_AST_VISITOR_H_
#define JISP_AST_VISITOR_H_

#include <memory>

#include "jisp/env.h"

class Value;
class NumberValue;
class StringValue;
class SymbolValue;
class SexprValue;
class FunctionValue;
class LambdaValue;

class ASTVisitor {
 public:
  explicit ASTVisitor(std::shared_ptr<Env> env) : enviroment(std::move(env)) {}

  std::unique_ptr<Value> visit(NumberValue* num);
  std::unique_ptr<Value> visit(StringValue* str);
  std::unique_ptr<Value> visit(FunctionValue* func);

  std::unique_ptr<Value> visit(SymbolValue* sym);
  std::unique_ptr<Value> visit(SexprValue* sexpr);
  std::unique_ptr<Value> visit(LambdaValue* sexpr);
  std::shared_ptr<Env> enviroment;
};
#endif
