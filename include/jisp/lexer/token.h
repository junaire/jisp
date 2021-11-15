#ifndef JISP_TOKEN_H_
#define JISP_TOKEN_H_

#include <string>

class Token {
 public:
  enum class Kind {
    // Type
    Integer,
    Float,
    Identifier,
    String,

    // Syntax
    LeftParen,
    RightParen,
    LeftSquare,
    RightSquare,

    // Comparison
    LessThan,
    GreaterThan,
    GreaterEqual,
    LessEqual,
    Equal,
    NotEqual,
    // Operator
    Plus,
    Minus,
    Multiply,
    Divide,
    PlusAssgin,
    MinusAssgin,
    MultiplyAssgin,
    DivideAssign,

    // Logical
    And,
    Or,

    // Keyword
    Define,
    If,
    While,
    Function,

    End,
    Unexpected,
  };

  Token(Kind kind, std::string value) : value(std::move(value)), kind_(kind) {}

  [[nodiscard]] const std::string& getValue() const { return value; }

  void setKind(Kind kind) { kind_ = kind; }

  [[nodiscard]] Kind getKind() const { return kind_; }

  [[nodiscard]] bool is(Kind kind) const { return kind_ == kind; }

  [[nodiscard]] bool isNot(Kind kind) const { return kind_ != kind; }

  [[nodiscard]] bool isOneOf(Kind k1, Kind k2) const {
    return is(k1) || is(k2);
  }

  bool isOneOf(Kind k1, Kind k2, auto&&... ks) const {
    return is(k1) || isOneOf(k2, ks...);
  }

 private:
  std::string value;
  Kind kind_;
};

#endif
