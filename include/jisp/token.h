#ifndef JISP_TOKEN_H_
#define JISP_TOKEN_H_

#include <string>

class Token {
 public:
  enum class Kind {
    Integer,
    Float,
    Identifier,
    String,
    LeftParen,
    RightParen,
    LeftSquare,
    RightSquare,
    LeftCurly,
    RightCurly,
    LessThan,
    GreaterThan,
    Equal,
    Plus,
    Minus,
    Multiply,
    Divide,
    Unexpected,
  };

  Token(Kind kind, std::string value) : kind_(kind), value(std::move(value)) {}

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
