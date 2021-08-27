#ifndef JISP_SYMBOL_VALUE_H_
#define JISP_SYMBOL_VALUE_H_

#include <memory>
#include <string>

#include "jisp/value.h"

class SymbolValue : public Value {
 public:
  SymbolValue(std::string name, std::unique_ptr<Value> value)
      : Value(Types::SYMBOL), name(name), value(std::move(value)) {}

  void inspect() override { value->inspect(); }

 private:
  std::string name;
  std::unique_ptr<Value> value;
};

#endif
