#ifndef JISP_STRING_VALUE_H_
#define JISP_STRING_VALUE_H_

#include <string>

#include "jisp/token.h"
#include "jisp/types.h"
#include "jisp/value.h"

class StringValue final : public Value {
 public:
  explicit StringValue(const Token& token) : StringValue(token.getValue()) {}
  explicit StringValue(std::string value)
      : value(std::move(value)), Value(ValueType::STRING) {}
  [[nodiscard]] std::string getValue() const { return value; }
  std::string inspect() override { return value; }
  std::unique_ptr<Value> accept(ASTVisitor& visitor) override;

 private:
  std::string value;
};

#endif
