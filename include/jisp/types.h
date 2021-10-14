#ifndef JISP_TYPES_H_
#define JISP_TYPES_H_

enum class ValueType { NUMBER, STRING, SYMBOL, FUNCTION, LAMBDA, SEXPR };

enum class TokenType {
  STRING,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  SYMBOL,
  NUMBER,
  LBRACKET,
  RBRACKET,
};
#endif
