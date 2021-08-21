#include "lexer.h"

// TODO: We don't care about ')', and other stuff like Symbol, String will be
// add to the AST later
std::shared_ptr<BaseValue> Lexer::parse() {
  // We need deal with the case if we only have one element
  std::shared_ptr<BaseValue> ast;
  std::shared_ptr<BaseValue> current;
  // We should recursively parse the AST
  if (tokens.size() == 1) {
    // literal things here
    // We need deal with other type like string, but we need refactor our
    // tokenizer
    if (isNumber(*tokens.begin()))
      return std::make_shared<Literal>(Types::NUMBER, *tokens.begin());
  }

  for (auto& token : tokens) {
    if (token == "(") {
      if (!ast) {
        ast = std::make_shared<Sexpr>(Types::SEXPR);
        current = ast;
      } else {
        auto tmp = std::make_shared<Sexpr>(Types::SEXPR);
        current->add(tmp);
        current = tmp;
      }

    } else if (isNumber(token)) {
      current->add(std::make_shared<Literal>(Types::NUMBER, token));
    } else {
      ast->add(std::make_shared<Symbol>(Types::SYMBOL, token, nullptr));
    }
  }
  return ast;
}

bool Lexer::isNumber(const std::string& s) {
  return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) {
                         return !std::isdigit(c);
                       }) == s.end();
}
