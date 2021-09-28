#ifndef JISP_PARSER_H_
#define JISP_PARSER_H_

#include <memory>
#include <string>
#include <vector>

#include "jisp/token.h"

class Value;
using Tokens = std::vector<Token>;

class Parser {
 public:
  explicit Parser(Tokens tokens) : tokens(std::move(tokens)), index(0) {}
  std::unique_ptr<Value> parse();

 private:
  std::unique_ptr<Value> parseSexpr();
  std::unique_ptr<Value> parseValue();
  Tokens tokens;
  size_t index;
};
#endif
