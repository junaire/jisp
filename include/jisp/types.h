#ifndef JISP_TYPES_H_
#define JISP_TYPES_H_

enum class Types {
  NUMBER,
  STRING,
  SYMBOL,
  LAMBDA,
};

enum class TokenType {
  STRING,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  SYMBOL,
  NUMBER,
  LBRACKET,
  RBRACKET
};
#endif
