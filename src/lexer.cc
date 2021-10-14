#include "jisp/lexer.h"

Tokens Lexer::tokenize(std::string_view input) {
  std::vector<Token> tokens;
  position = 0;
  length = input.length();

  while (position < length) {
    if (auto token = lex(input)) {
      tokens.push_back(std::move(*token));
    }
  }
  return tokens;
}

std::optional<Token> Lexer::lex(std::string_view code) {
  skipWhiteSpace(code);
  if (auto value = lexSyntax(code)) return value;
  if (auto value = lexOperator(code)) return value;
  if (auto value = lexNumber(code)) return value;
  if (auto value = lexString(code)) return value;
  if (auto value = lexSymbol(code)) return value;
  return std::nullopt;
}

std::optional<Token> Lexer::lexNumber(const std::string_view code) {
  std::string value{code[position]};
  if (!std::isdigit(code[position])) return std::nullopt;
  advance();
  while (true) {
    if (std::isdigit(code[position]) || code[position] == '.') {
      value += code[position];
      advance();
    } else {
      break;
    }
  }
  return Token(TokenType::NUMBER, value);
}

std::optional<Token> Lexer::lexString(const std::string_view code) {
  std::string value;
  if (code[position] != '"') {
    return std::nullopt;
  }
  advance();
  while (true) {
    if (code[position] == '"') {
      advance();
      break;
    }
    value += code[position];
    advance();
  }

  return Token(TokenType::STRING, value);
}

std::optional<Token> Lexer::lexSymbol(const std::string_view code) {
  std::string value{code[position]};
  if (!std::isalpha(code[position])) return std::nullopt;
  advance();
  while (true) {
    if (!std::isalpha(code[position])) {
      break;
    }
    value += code[position];
    advance();
  }

  return Token(TokenType::SYMBOL, value);
}

void Lexer::skipWhiteSpace(std::string_view code) {
  if (!std::isspace(code[position])) {
    return;
  }

  while (true) {
    if (std::isspace(code[position])) {
      advance();
      continue;
    }
    return;
  }
}

std::optional<Token> Lexer::lexSyntax(const std::string_view code) {
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

std::optional<Token> Lexer::lexOperator(const std::string_view code) {
  auto current = code[position];
  switch (current) {
    case '+':
      advance();
      return Token(TokenType::PLUS, std::string(1, current));
    case '-':
      advance();
      return Token(TokenType::MINUS, std::string(1, current));
    case '*':
      advance();
      return Token(TokenType::MULTIPLY, std::string(1, current));
    case '/':
      advance();
      return Token(TokenType::DIVIDE, std::string(1, current));
    default:
      return std::nullopt;
  }
}

void Lexer::advance() {
  if (position < length) {
    ++position;
  }
}
