#ifndef JISP_STRING_VALUE_H_
#define JISP_STRING_VALUE_H_

#include <iostream>
#include <string>

#include "jisp/token.h"
#include "jisp/types.h"
#include "jisp/value.h"

class StringValue final : public Value {
 public:
  StringValue(const Token& token) : StringValue(token.getValue()) {}
  StringValue(const std::string& value) : Value(Types::STRING), value(value) {}
  std::string getValue() const { return value; }
  void inspect() override { std::cout << value; }

 private:
  std::string value;
};

#endif
