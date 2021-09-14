#ifndef JISP_SYMBOL_VALUE_H_
#define JISP_SYMBOL_VALUE_H_

#include <fmt/format.h>

#include <memory>
#include <string>

#include "jisp/token.h"
#include "jisp/value.h"

class SymbolValue : public Value {
 public:
  explicit SymbolValue(const Token& token)
      : SymbolValue(token.getValue(), nullptr) {}
  SymbolValue(std::string name, std::unique_ptr<Value> value)
      : Value(Types::SYMBOL), name(std::move(name)), value(std::move(value)) {}

  void inspect() override { fmt::print("Symbol: {}\n", name); }
  [[nodiscard]] std::string getName() const { return name; }

 private:
  std::string name;
  std::unique_ptr<Value> value;
};

#endif
