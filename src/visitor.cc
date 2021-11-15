#include "jisp/ast/visitor.h"

#include "jisp/ast/ast.h"
#include "jisp/ast/builtin.h"
#include "jisp/env.h"
#include "jisp/value/value.h"

Value Visitor::visit(Block* node) {
  if (node->elem_.size() == 1) {
    return node->elem_[0]->exec(*this);
  }

  Value value;
  for (auto& n : node->elem_) {
    value = n->exec(*this);
  }
  return value;
}

[[maybe_unused]] Value Visitor::visit(List* node) {
  // Just skip this, we don't have to do anything about it.
  return Value();
}

Value Visitor::visit(BinaryExpression* node) {
  std::vector args{node->lhs_.get(), node->rhs_.get()};
  return node->op_->apply(*this, args);
}

// TODO(Jun): How to deal with functions?
Value Visitor::visit(Function* node) {
  auto fnName = node->id_->toIdentifier()->name();
  env->set(fnName, node);
  return Value(fnName);
}

Value Visitor::visit(CallExpression* node) {
  Visitor localVisitor{env};

  auto* fn = env->get(node->callee_->toIdentifier()->name())->toFunction();

  for (int i = 0; i < fn->params_->toList()->size(); i++) {
    localVisitor.env->set(fn->params_->toList()->at(i)->toIdentifier()->name(),
                          node->arguments_->toBlock()->at(i));
  }
  return localVisitor.visit(fn->body_->toBlock());
}

Value Visitor::visit(Identifier* node) {
  auto* id = env->get(node->toIdentifier()->name());
  return id->exec(*this);
}

Value Visitor::visit(IfExpression* node) {
  bool test = node->test_->exec(*this).toBoolean();
  if (test) {
    return node->consequent_->exec(*this);
  }
  return node->alternate_->exec(*this);
}

Value Visitor::visit(WhileExpression* node) {
  Value ret;
  while (node->test_->exec(*this).toBoolean()) {
    ret = node->body_->exec(*this);
  }
  return ret;
}

Value Visitor::visit(Declaretion* node) {
  auto var = node->id_->toIdentifier()->name_;
  this->env->set(var, node->init_.get());
  return Value(var);
}

Value Visitor::visit(Literal* node) { return node->value_; }

