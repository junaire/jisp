#ifndef JISP_VALUE_H_
#define JISP_VALUE_H_

#include <memory>
#include <string>
class ASTVisitor;

class NumberValue;
class StringValue;
class SymbolValue;
class FunctionValue;
class SexprValue;

class Value {
 public:
  Value() = default;

  NumberValue* toNumber();
  StringValue* toString();
  SymbolValue* toSymbol();
  SexprValue* toSexpr();
  FunctionValue* toFunction();

  virtual std::unique_ptr<Value> accept(ASTVisitor&) = 0;
  virtual std::string inspect() = 0;
  virtual ~Value() = default;
};
#endif
