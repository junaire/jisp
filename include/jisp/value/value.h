#ifndef JISP_VALUE_
#define JISP_VALUE_

#include <fmt/format.h>

#include <string>
#include <variant>

class Value {
  using JispValue = std::variant<int, std::string, bool, std::nullptr_t>;

 public:
  enum class Kind { Int, String, Bool, Void };

  explicit Value(int val) : val_(val), kind_(Kind::Int) {}

  explicit Value(bool val) : val_(val), kind_(Kind::Bool) {}

  explicit Value(std::string val) : val_(std::move(val)), kind_(Kind::String) {}

  explicit Value(std::nullptr_t val) : val_(val), kind_(Kind::Void) {}

  Value() : Value(nullptr) {}

  [[nodiscard]] int toNumber() const {
    // Do some implicit conversions
    if (isBool()) {
      return static_cast<int>(std::get<bool>(val_));
    }
    return std::get<int>(val_);
  }

  [[nodiscard]] std::string toString() const {
    return std::get<std::string>(val_);
  }

  [[nodiscard]] bool toBoolean() const {
    if (isNumber()) {
      return static_cast<bool>(std::get<int>(val_));
    }
    if (isString()) {
      return static_cast<bool>(!std::get<std::string>(val_).empty());
    }
    return std::get<bool>(val_);
  }

  void print() {
    // FIXME: This is a completely a hack, do we have type like void_t in C++?
    if (isVoid()) {
      return;
    }
    std::visit([](const auto& val) { fmt::print("{}\n", val); }, val_);
  }

  [[nodiscard]] bool isNumber() const { return kind_ == Kind::Int; }

  [[nodiscard]] bool isString() const { return kind_ == Kind::String; }

  [[nodiscard]] bool isBool() const { return kind_ == Kind::Bool; }

  [[nodiscard]] bool isVoid() const { return kind_ == Kind::Void; }

  // TODO(Jun): Now we only support reset ASTNode's value with Literal type,
  // need to expand
  void reset(JispValue val) { val_ = std::move(val); }

  std::string toString() {
    if (isString()) {
      return std::get<std::string>(val_);
    }
    if (isBool()) {
      return std::get<bool>(val_) ? "true" : "false";
    }
    if (isNumber()) {
      return std::to_string(std::get<int>(val_));
    }
    return "";
  }

 private:
  JispValue val_;
  Kind kind_;
};

#endif
