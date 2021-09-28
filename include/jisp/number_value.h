#ifndef JISP_NUMBER_VALUE_H_
#define JISP_NUMBER_VALUE_H_

#include <fmt/format.h>

#include "jisp/token.h"
#include "jisp/value.h"

class NumberValue : public Value {
 public:
  explicit NumberValue(const Token& token) : NumberValue(token.getValue()) {}
  explicit NumberValue(const std::string& val) : value(std::stoi(val)) {}
  explicit NumberValue(int val) : value(val) {}

  std::string inspect() override { return fmt::format("{}", value); }

  std::unique_ptr<Value> accept(ASTVisitor& visitor) override;

  [[nodiscard]] int getValue() const { return value; }

 private:
  int value;
};
#endif
