#include "jisp/ast/ast.h"

#include <fmt/format.h>

#include "jisp/ast/builtin.h"
#include "jisp/ast/visitor.h"

void insertIndent(int n) {
  for (int i = 0; i < n; i++) {
    fmt::print(" ");
  }
}

Identifier* ASTNode::toIdentifier() { return static_cast<Identifier*>(this); }

Block* ASTNode::toBlock() { return static_cast<Block*>(this); }

List* ASTNode::toList() { return static_cast<List*>(this); }

BinaryExpression* ASTNode::toBinaryExpression() {
  return static_cast<BinaryExpression*>(this);
}

CallExpression* ASTNode::toCallExpression() {
  return static_cast<CallExpression*>(this);
}

IfExpression* ASTNode::toIfExpression() {
  return static_cast<IfExpression*>(this);
}

WhileExpression* ASTNode::toWhileExpression() {
  return static_cast<WhileExpression*>(this);
}

Declaration* ASTNode::toDeclaretion() {
  return static_cast<Declaration*>(this);
}

Function* ASTNode::toFunction() { return static_cast<Function*>(this); }

Literal* ASTNode::toLiteral() { return static_cast<Literal*>(this); }

Builtin* ASTNode::toBuiltin() { return static_cast<Builtin*>(this); }

Value BinaryExpression::exec(Visitor& visitor) { return visitor.visit(this); }

void BinaryExpression::dump(int indent) const {
  insertIndent(indent);
  fmt::print("BinaryExpression\n");
  op_->dump(indent + 2);
  lhs_->dump(indent + 2);
  rhs_->dump(indent + 2);
}

Value Block::exec(Visitor& visitor) { return visitor.visit(this); }

void Block::dump(int indent) const {
  insertIndent(indent);
  fmt::print("Block\n");
  for (const auto& ele : elem_) {
    ele->dump(indent + 2);
  }
}

Value CallExpression::exec(Visitor& visitor) { return visitor.visit(this); }

void CallExpression::dump(int indent) const {
  insertIndent(indent);
  fmt::print("CallExpression\n");
  callee_->dump(indent + 2);
  arguments_->dump(indent + 2);
}

Value Declaration::exec(Visitor& visitor) { return visitor.visit(this); }

void Declaration::dump(int indent) const {
  insertIndent(indent);
  fmt::print("Declaretion\n");
  id_->dump(indent + 2);
  init_->dump(indent + 2);
}

Value Function::exec(Visitor& visitor) { return visitor.visit(this); }

void Function::dump(int indent) const {
  insertIndent(indent);
  fmt::print("Function\n");
  id_->dump(indent + 2);
  params_->dump(indent + 2);
  body_->dump(indent + 2);
}

Value Identifier::exec(Visitor& visitor) { return visitor.visit(this); }

void Identifier::dump(int indent) const {
  insertIndent(indent);
  fmt::print("Identifier: {}\n", this->name_);
}

Value IfExpression::exec(Visitor& visitor) { return visitor.visit(this); }

void IfExpression::dump(int indent) const {
  insertIndent(indent);
  fmt::print("IfExpression\n");
  test_->dump(indent + 2);
  test_->dump(indent + 2);
  alternate_->dump(indent + 2);
  alternate_->dump(indent + 2);
}

Value WhileExpression::exec(Visitor& visitor) { return visitor.visit(this); }

void WhileExpression::dump(int indent) const {
  insertIndent(indent);
  fmt::print("WhileExpression\n");
  test_->dump(indent + 2);
  body_->dump(indent + 2);
}

Value List::exec(Visitor& visitor) { return visitor.visit(this); }

void List::dump(int indent) const {
  insertIndent(indent);
  fmt::print("List\n");
  for (const auto& ele : elem_) {
    ele->dump(indent + 2);
  }
}

Value Literal::exec(Visitor& visitor) { return visitor.visit(this); }

void Literal::dump(int indent) const {
  insertIndent(indent);
  fmt::print("Literal: {}\n", value_.toString());
}

void Builtin::dump(int indent) const {
  insertIndent(indent);
  // FIXME: We can't know what kind of builtin operators it is...
  fmt::print("Builtin\n");
}
