#ifndef JISP_STRING_VALUE_H_
#define JISP_STRING_VALUE_H_

#include <fmt/format.h>

#include <string>

#include "jisp/token.h"
#include "jisp/types.h"
#include "jisp/value.h"

class StringValue final : public Value {
 public:
  explicit StringValue(const Token& token) : StringValue(token.getValue()) {}
  explicit StringValue(std::string value)
      : Value(Types::STRING), value(std::move(value)) {}
  [[nodiscard]] std::string getValue() const { return value; }
  void inspect() override { fmt::print("String: {}\n", value); }

 private:
  std::string value;
};

#endif
