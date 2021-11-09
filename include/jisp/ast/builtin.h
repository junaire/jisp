#ifndef JISP_AST_BUILTIN_
#define JISP_AST_BUILTIN_

class Value;
class Visitor;
#include <fmt/format.h>

#include <memory>
#include <vector>

#include "jisp/ast/ast.h"

class Builtin : public ASTNode {
 public:
  // FIXME: I don't like vector in function argument
  virtual Value apply(Visitor& visitor, std::vector<Value>& args) = 0;
  [[maybe_unused]] void dump() const final { fmt::print("Builtin"); };
  [[maybe_unused]] Value exec(Visitor& visitor) final { return Value(); }
};

class Add : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<Value>& args) override;
};

class Sub : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<Value>& args) override;
};

class Multiply : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<Value>& args) override;
};

class Divide : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<Value>& args) override;
};

class Greater : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<Value>& args) override;
};

class Less : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<Value>& args) override;
};

class Equal : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<Value>& args) override;
};

class NotEqual : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<Value>& args) override;
};

class GreaterEqual : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<Value>& args) override;
};

class LessEqual : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<Value>& args) override;
};

class And : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<Value>& args) override;
};

class Or : public Builtin {
 public:
  Value apply(Visitor& visitor, std::vector<Value>& args) override;
};

#endif
