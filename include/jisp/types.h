#ifndef JISP_TYPES_H_
#define JISP_TYPES_H_

enum class Types {
  NUMBER,
  STRING,
  SYMBOL,
  LAMBDA,
};

enum class TokenType {
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  NAME,
  NUMBER,
  LBRACKET,
  RBRACKET
};
#endif
