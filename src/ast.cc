#include "jisp/ast/ast.h"

#include <fmt/format.h>

#include "jisp/ast/builtin.h"
#include "jisp/ast/visitor.h"

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

Declaretion* ASTNode::toDeclaretion() {
  return static_cast<Declaretion*>(this);
}

Function* ASTNode::toFunction() { return static_cast<Function*>(this); }

Literal* ASTNode::toLiteral() { return static_cast<Literal*>(this); }

Builtin* ASTNode::toBuiltin() { return static_cast<Builtin*>(this); }

Value BinaryExpression::exec(Visitor& visitor) { return visitor.visit(this); }

void BinaryExpression::dump() const { fmt::print("BinaryExpression"); }

Value Block::exec(Visitor& visitor) { return visitor.visit(this); }

void Block::dump() const {
  fmt::print("Block\n");
  for (const auto& ele : elem_) {
    ele->dump();
  }
}

Value CallExpression::exec(Visitor& visitor) { return visitor.visit(this); }

void CallExpression::dump() const { fmt::print("CallExpression"); }

Value Declaretion::exec(Visitor& visitor) { return visitor.visit(this); }

void Declaretion::dump() const { fmt::print("Declaretion"); }

Value Function::exec(Visitor& visitor) { return visitor.visit(this); }

void Function::dump() const { fmt::print("Function"); }

Value Identifier::exec(Visitor& visitor) { return visitor.visit(this); }

void Identifier::dump() const { fmt::print("{}", this->name_); }

Value IfExpression::exec(Visitor& visitor) { return visitor.visit(this); }

void IfExpression::dump() const { fmt::print("IfExpression"); }

Value WhileExpression::exec(Visitor& visitor) { return visitor.visit(this); }

void WhileExpression::dump() const { fmt::print("WhileExpression"); }

Value List::exec(Visitor& visitor) { return visitor.visit(this); }

void List::dump() const { fmt::print("List"); }

Value Literal::exec(Visitor& visitor) { return visitor.visit(this); }

void Literal::dump() const { fmt::print("Literal"); }
