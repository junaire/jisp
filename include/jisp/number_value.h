#ifndef JISP_NUMBER_VALUE_H_
#define JISP_NUMBER_VALUE_H_

#include <fmt/format.h>

#include "jisp/types.h"
#include "jisp/value.h"
class NumberValue final : public Value {
 public:
  NumberValue(std::string val) : Value(Types::NUMBER), value(std::stoi(val)) {}

  void inspect() override { fmt::print("{}\n", value); }

  int getValue() { return value; }

 private:
  int value;
};
#endif