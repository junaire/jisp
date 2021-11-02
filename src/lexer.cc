#include "jisp/lexer.h"

Tokens Lexer::tokenize() {
  std::vector<Token> tokens;
  while (position < input_.length()) {
    tokens.push_back(*next());
  }
  return tokens;
}

void Lexer::advance() {
  if (position < input_.length()) {
    ++position;
  }
}

char Lexer::peek() { return input_[position]; }

char Lexer::get() { return input_.at(position++); }

bool Lexer::isValidChar(char c) {
  bool flag = false;
  if (c >= 'A' && c <= 'Z') {
    flag = true;
  }

  if (c >= 'a' && c <= 'z') {
    flag = true;
  }

  if (c == '_') {
    flag = true;
  }

  return flag;
}

// TODO(Jun): Add support for floating number
Token Lexer::number() {
  std::string value{get()};

  while (true) {
    char c = peek();
    if (std::isdigit(c) != 0 || c == '.') {
      value += c;
      advance();
    } else {
      break;
    }
  }
  return Token(Token::Kind::Integer, std::move(value));
}

Token Lexer::str() {
  std::string value{"\""};
  advance();
  while (true) {
    char c = get();
    if (c == '"') {
      break;
    }
    value += c;
  }

  value += "\"";

  return Token(Token::Kind::String, std::move(value));
}

Token Lexer::identifier() {
  std::string value{get()};

  while (true) {
    char c = peek();
    if (!isValidChar(c)) {
      break;
    }
    value += c;
    advance();
  }

  return Token(Token::Kind::Identifier, std::move(value));
}

void Lexer::skipWhiteSpace() {
  while (true) {
    if (std::isspace(peek()) == 0) {
      return;
    }
    advance();
  }
}

Token Lexer::atom(Token::Kind kind) {
  return Token(kind, std::string(1, get()));
}

std::optional<Token> Lexer::next() {
  skipWhiteSpace();

  switch (peek()) {
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
      return identifier();
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return number();
    case '(':
      return atom(Token::Kind::LeftParen);
    case ')':
      return atom(Token::Kind::RightParen);
    case '[':
      return atom(Token::Kind::LeftSquare);
    case ']':
      return atom(Token::Kind::RightSquare);
    case '{':
      return atom(Token::Kind::LeftCurly);
    case '}':
      return atom(Token::Kind::RightCurly);
    case '<':
      return atom(Token::Kind::LessThan);
    case '>':
      return atom(Token::Kind::GreaterThan);
    case '=':
      return atom(Token::Kind::Equal);
    case '+':
      return atom(Token::Kind::Plus);
    case '-':
      return atom(Token::Kind::Minus);
    case '*':
      return atom(Token::Kind::Multiply);
    case '/':
      return atom(Token::Kind::Divide);
    case '"':
      return str();
      /*
        case '.':
          return atom(Token::Kind::Dot);
        case ',':
          return atom(Token::Kind::Comma);
        case ':':
          return atom(Token::Kind::Colon);
        case ';':
          return atom(Token::Kind::Semicolon);
      */
    default:
      return atom(Token::Kind::Unexpected);
  }
}

