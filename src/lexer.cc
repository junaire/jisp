#include "jisp/lexer.h"

Tokens Lexer::tokenize() {
  std::vector<Token> tokens;

  while (position < length) {
    if (auto token = lex(code)) {
      tokens.push_back(std::move(*token));
    }
  }
  return tokens;
}

std::optional<Token> Lexer::lex(const std::string& code) {
  skipWhiteSpace();
  if (auto value = lexSyntax(code)) return value;
  if (auto value = lexOperator(code)) return value;
  if (auto value = lexNumber(code)) return value;
  if (auto value = lexString(code)) return value;
  if (auto value = lexSymbol(code)) return value;
  return std::nullopt;
}

std::optional<Token> Lexer::lexNumber(const std::string& code) {
  std::string value{code[position]};
  if (!std::isdigit(code[position])) return std::nullopt;
  advance();
  while (true) {
    if (std::isdigit(code[position]) || code[position] == '.') {
      value += code[position];
      advance();
    } else
      break;
  }
  return Token(TokenType::NUMBER, value);
}

std::optional<Token> Lexer::lexString(const std::string& code) {
  std::string value{code[position]};
  if (code[position] != '"') return std::nullopt;
  advance();
  while (true) {
    if (code[position] == '"')
      break;
    else {
      value += code[position];
      advance();
    }
  }
  return Token(TokenType::STRING, value);
}

std::optional<Token> Lexer::lexSymbol(const std::string& code) {
  std::string value{code[position]};
  if (!std::isalpha(code[position])) return std::nullopt;
  advance();
  while (true) {
    if (!std::isalpha(code[position]))
      break;
    else {
      value += code[position];
      advance();
    }
  }
  return Token(TokenType::SYMBOL, value);
}

void Lexer::skipWhiteSpace() {
  if (!std::isspace(code[position])) return;

  while (true) {
    if (std::isspace(code[position])) {
      advance();
      continue;
    } else {
      return;
    }
  }
}

std::optional<Token> Lexer::lexSyntax(const std::string& code) {
  auto current = code[position];
  switch (current) {
    case '(':
      advance();
      return Token(TokenType::LBRACKET, std::string(1, current));
    case ')':
      advance();
      return Token(TokenType::RBRACKET, std::string(1, current));
    default:
      return std::nullopt;
  }
}

std::optional<Token> Lexer::lexOperator(const std::string& code) {
  auto current = code[position];
  switch (current) {
    case '+':
      advance();
      return Token(TokenType::PLUS, std::string(1, current));
    case '-':
      advance();
      return Token(TokenType::MINUS, std::string(1, current));
    case '*':
      return Token(TokenType::MULTIPLY, std::string(1, current));
    case '/':
      return Token(TokenType::DIVIDE, std::string(1, current));
    default:
      return std::nullopt;
  }
}

void Lexer::advance() {
  if (position < length) ++position;
}
