#ifndef JISP_NUMBER_VALUE_H_
#define JISP_NUMBER_VALUE_H_

#include <fmt/format.h>

#include "jisp/token.h"
#include "jisp/types.h"
#include "jisp/value.h"
class NumberValue final : public Value {
 public:
  explicit NumberValue(const Token& token) : NumberValue(token.getValue()) {}
  explicit NumberValue(const std::string& val)
      : Value(Types::NUMBER), value(std::stoi(val)) {}
  explicit NumberValue(int val) : Value(Types::NUMBER), value(val) {}

  void inspect() override { fmt::print("{}\n", value); }

  [[nodiscard]] int getValue() const { return value; }

 private:
  int value;
};
#endif
