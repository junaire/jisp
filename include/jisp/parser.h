#ifndef JISP_PARSER_H_
#define JISP_PARSER_H_

#include <memory>
#include <string>
#include <vector>

#include "jisp/token.h"

class Value;
using Tokens = std::vector<Token>;
using ValuePtr = std::shared_ptr<Value>;

class Parser {
 public:
  explicit Parser(Tokens tokens) : tokens(std::move(tokens)), index(0) {}
  ValuePtr parse();

 private:
  ValuePtr parseSexpr();
  ValuePtr parseValue();
  Tokens tokens;
  size_t index;
};
#endif
