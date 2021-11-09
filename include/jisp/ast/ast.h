#ifndef JISP_AST_
#define JISP_AST_

#include <memory>
#include <vector>

#include "jisp/value/value.h"

class Visitor;
class Identifier;
class CallExpression;
class IfExpression;
class BinaryExpression;
class Block;
class List;
class Declaretion;
class Literal;
class Function;
class Builtin;

class ASTNode {
 public:
  ASTNode() = default;

  virtual Value exec(Visitor& visitor) = 0;
  virtual void dump() const = 0;

  Identifier* toIdentifier();
  CallExpression* toCallExpression();
  BinaryExpression* toBinaryExpression();
  IfExpression* toIfExpression();
  Block* toBlock();
  List* toList();
  Declaretion* toDeclaretion();
  Literal* toLiteral();
  Function* toFunction();

  Builtin* toBuiltin();

  ASTNode(const ASTNode&) = delete;
  ASTNode& operator=(const ASTNode&) = delete;
  ASTNode(ASTNode&&) = default;
  ASTNode& operator=(ASTNode&&) = default;

  virtual ~ASTNode() = default;
};

class Identifier : public ASTNode {
  friend class Visitor;

 public:
  explicit Identifier(std::string name) : name_(std::move(name)) {}

  void dump() const override;
  Value exec(Visitor& visitor) override;

  [[nodiscard]] const std::string& name() const { return name_; }

 private:
  std::string name_;
};

class List : public ASTNode {
  friend class Visitor;

 public:
  List() = default;

  void append(std::unique_ptr<ASTNode> node) {
    elem_.push_back(std::move(node));
  }

  [[nodiscard]] auto size() const { return elem_.size(); }
  [[nodiscard]] bool empty() const { return elem_.empty(); }

  [[nodiscard]] ASTNode* at(int index) { return elem_.at(index).get(); }

  std::unique_ptr<ASTNode> drop(int index) {
    auto node = std::move(elem_.at(index));
    elem_.erase(elem_.begin() + index);
    return node;
  }

  void dump() const override;
  Value exec(Visitor& visitor) override;

 private:
  std::vector<std::unique_ptr<ASTNode>> elem_;
};

class Literal : public ASTNode {
  friend class Visitor;

 public:
  explicit Literal(auto&& value) : value_(std::move(value)) {}

  void dump() const override;
  Value exec(Visitor& visitor) override;

 private:
  Value value_;
};

class Block : public ASTNode {
  friend class Visitor;

 public:
  Block() = default;

  void append(std::unique_ptr<ASTNode> node) {
    elem_.push_back(std::move(node));
  }

  [[nodiscard]] auto size() const { return elem_.size(); }
  [[nodiscard]] bool empty() const { return elem_.empty(); }

  [[nodiscard]] ASTNode* at(int index) { return elem_.at(index).get(); }

  // FIXME: drop the node, instead of setting the orginal value to nullptr
  std::unique_ptr<ASTNode> drop(int index = 0) {
    auto node = std::move(elem_.at(index));
    elem_.erase(elem_.begin() + index);
    return node;
  }

  void dump() const override;
  Value exec(Visitor& visitor) override;

 private:
  std::vector<std::unique_ptr<ASTNode>> elem_;
};

class BinaryExpression : public ASTNode {
  friend class Visitor;

 public:
  BinaryExpression(std::unique_ptr<Builtin> op, std::unique_ptr<ASTNode> lhs,
                   std::unique_ptr<ASTNode> rhs)
      : op_(std::move(op)), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

  Value exec(Visitor& visitor) override;
  void dump() const override;

 private:
  std::unique_ptr<Builtin> op_;
  std::unique_ptr<ASTNode> lhs_;
  std::unique_ptr<ASTNode> rhs_;
};

class CallExpression : public ASTNode {
  friend class Visitor;

 public:
  CallExpression(std::unique_ptr<ASTNode> callee,
                 std::unique_ptr<ASTNode> arguments)
      : callee_(std::move(callee)), arguments_(std::move(arguments)) {}

  void dump() const override;
  Value exec(Visitor& visitor) override;

 private:
  std::unique_ptr<ASTNode> callee_;
  std::unique_ptr<ASTNode> arguments_;
};

class Declaretion : public ASTNode {
  friend class Visitor;

 public:
  Declaretion(std::unique_ptr<ASTNode> id, std::unique_ptr<ASTNode> init)
      : id_(std::move(id)), init_(std::move(init)) {}

  void dump() const override;
  Value exec(Visitor& visitor) override;

 private:
  std::unique_ptr<ASTNode> id_;
  std::unique_ptr<ASTNode> init_;
};

class Function : public ASTNode {
  friend class Visitor;

 public:
  Function(std::unique_ptr<ASTNode> id, std::unique_ptr<ASTNode> params,
           std::unique_ptr<ASTNode> body)
      : id_(std::move(id)),
        params_(std::move(params)),
        body_(std::move(body)) {}

  void dump() const override;
  Value exec(Visitor& visitor) override;

 private:
  std::unique_ptr<ASTNode> id_;
  std::unique_ptr<ASTNode> params_;
  std::unique_ptr<ASTNode> body_;
};

class IfExpression : public ASTNode {
  friend class Visitor;

 public:
  IfExpression(std::unique_ptr<ASTNode> test,
               std::unique_ptr<ASTNode> consequent,
               std::unique_ptr<ASTNode> alternate)
      : test_(std::move(test)),
        consequent_(std::move(consequent)),
        alternate_(std::move(alternate)){};

  void dump() const override;
  Value exec(Visitor& visitor) override;

 private:
  std::unique_ptr<ASTNode> test_;
  std::unique_ptr<ASTNode> consequent_;
  std::unique_ptr<ASTNode> alternate_;
};

#endif
