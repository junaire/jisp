#ifndef JISP_AST_BUILTIN_
#define JISP_AST_BUILTIN_

class Value;
class Visitor;
#include <fmt/format.h>

#include <memory>
#include <string_view>
#include <vector>

#include "jisp/ast/ast.h"

class Builtin : public ASTNode {
 public:
  // FIXME: I don't like vector in function argument
  virtual Value apply(Visitor& visitor, std::vector<ASTNode*>& args) = 0;
  void dump(int indent) const final;
  [[maybe_unused]] Value exec(Visitor& visitor) final { return Value(); }
  [[nodiscard]] virtual std::string_view type() const = 0;
};

class Add : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<ASTNode*>& args) override;
  [[nodiscard]] std::string_view type() const override { return "+"; };
};

class Sub : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<ASTNode*>& args) override;
  [[nodiscard]] std::string_view type() const override { return "-"; };
};

class Multiply : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<ASTNode*>& args) override;
  [[nodiscard]] std::string_view type() const override { return "*"; };
};

class Divide : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<ASTNode*>& args) override;
  [[nodiscard]] std::string_view type() const override { return "/"; };
};

class Greater : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<ASTNode*>& args) override;
  [[nodiscard]] std::string_view type() const override { return ">"; };
};

class Less : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<ASTNode*>& args) override;
  [[nodiscard]] std::string_view type() const override { return "<"; };
};

class Equal : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<ASTNode*>& args) override;
  [[nodiscard]] std::string_view type() const override { return "=="; };
};

class NotEqual : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<ASTNode*>& args) override;
  [[nodiscard]] std::string_view type() const override { return "!="; };
};

class GreaterEqual : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<ASTNode*>& args) override;
  [[nodiscard]] std::string_view type() const override { return ">="; };
};

class LessEqual : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<ASTNode*>& args) override;
  [[nodiscard]] std::string_view type() const override { return "<="; };
};

class And : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<ASTNode*>& args) override;
  [[nodiscard]] std::string_view type() const override { return "&&"; };
};

class Or : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<ASTNode*>& args) override;
  [[nodiscard]] std::string_view type() const override { return "||"; };
};

class AddAssign : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<ASTNode*>& args) override;
  [[nodiscard]] std::string_view type() const override { return "+="; };
};

class SubAssign : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<ASTNode*>& args) override;
  [[nodiscard]] std::string_view type() const override { return "-="; };
};

class MultiplyAssgin : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<ASTNode*>& args) override;
  [[nodiscard]] std::string_view type() const override { return "*="; };
};

class DivideAssign : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<ASTNode*>& args) override;
  [[nodiscard]] std::string_view type() const override { return "/="; };
};

#endif
