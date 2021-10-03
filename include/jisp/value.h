#ifndef JISP_VALUE_H_
#define JISP_VALUE_H_

#include <memory>
#include <string>

#include "jisp/types.h"

class ASTVisitor;

class NumberValue;
class StringValue;
class SymbolValue;
class FunctionValue;
class SexprValue;
class LambdaValue;

class Value {
 public:
  explicit Value(ValueType tp) : type(tp){};
  virtual ~Value() = default;

  NumberValue* toNumber();
  StringValue* toString();
  SymbolValue* toSymbol();
  SexprValue* toSexpr();
  FunctionValue* toFunction();
  LambdaValue* toLambda();

  [[nodiscard]] bool isNumber() const { return type == ValueType::NUMBER; }
  [[nodiscard]] bool isString() const { return type == ValueType::STRING; }
  [[nodiscard]] bool isSymbol() const { return type == ValueType::SYMBOL; }
  [[nodiscard]] bool isSexpr() const { return type == ValueType::SEXPR; }
  [[nodiscard]] bool isFunction() const { return type == ValueType::FUNCTION; }
  [[nodiscard]] bool isLambda() const { return type == ValueType::LAMBDA; }

  virtual std::unique_ptr<Value> accept(ASTVisitor&) = 0;
  virtual std::string inspect() = 0;

 private:
  ValueType type;
};
#endif
