#ifndef JISP_PARSER_H_
#define JISP_PARSER_H_

#include <memory>
#include <string>
#include <vector>

#include "jisp/lambda_value.h"
#include "jisp/number_value.h"
#include "jisp/symbol_value.h"
#include "jisp/token.h"
#include "jisp/value.h"

using Tokens = std::vector<Token>;
using ValuePtr = std::shared_ptr<Value>;
class Parser {
 public:
  Parser(const Tokens& tokens) : tokens(tokens) {}
  ValuePtr parse();

 private:
  Tokens tokens;
};
#endif
