#ifndef JISP_SYMBOL_VALUE_H_
#define JISP_SYMBOL_VALUE_H_

#include <fmt/format.h>

#include <memory>
#include <string>

#include "jisp/token.h"
#include "jisp/types.h"
#include "jisp/value.h"

class SymbolValue final : public Value {
 public:
  explicit SymbolValue(const Token& token)
      : SymbolValue(token.getValue(), nullptr) {}
  SymbolValue(std::string name, std::unique_ptr<Value> value)
      : name(std::move(name)), value(value), Value(ValueType::SYMBOL) {}

  std::string inspect() override { return value->inspect(); }
  std::unique_ptr<Value> accept(ASTVisitor& visitor) override;
  [[nodiscard]] std::string getName() const { return name; }

 private:
  std::string name;
  std::unique_ptr<Value>& value;
};

#endif
