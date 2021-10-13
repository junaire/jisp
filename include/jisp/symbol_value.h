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
  explicit SymbolValue(const Token& token) : SymbolValue(token.getValue()) {}
  explicit SymbolValue(std::string name)
      : name(std::move(name)), Value(ValueType::SYMBOL) {}

  std::string inspect() override { return "<Symbol>"; }
  std::unique_ptr<Value> accept(ASTVisitor& visitor) override;
  [[nodiscard]] bool isLiteral() const override { return false; }
  [[nodiscard]] std::string getName() const { return name; }
  std::unique_ptr<Value> clone() override {
    return std::make_unique<SymbolValue>(name);
  }

 private:
  std::string name;
};

#endif
