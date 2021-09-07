#ifndef JISP_SYMBOL_VALUE_H_
#define JISP_SYMBOL_VALUE_H_

#include <memory>
#include <string>

#include "jisp/token.h"
#include "jisp/value.h"

class SymbolValue : public Value {
 public:
  SymbolValue(const Token& token) : SymbolValue(token.getValue(), nullptr) {}
  SymbolValue(std::string name, std::unique_ptr<Value> value)
      : Value(Types::SYMBOL), name(std::move(name)), value(std::move(value)) {}

  void inspect() override { value->inspect(); }
  std::string getName() const { return name; }

 private:
  std::string name;
  std::unique_ptr<Value> value;
};

#endif
