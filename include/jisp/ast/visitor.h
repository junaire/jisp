#ifndef JISP_AST_VISITOR_
#define JISP_AST_VISITOR_

class Value;
class ASTNode;
class Identifier;
class Literal;
class Declaration;
class Function;
class IfExpression;
class WhileExpression;
class BinaryExpression;
class Block;
class List;
class CallExpression;

#include <memory>

#include "jisp/env.h"

class Visitor {
 public:
  explicit Visitor(Env* en) : env(en) {}

  Value visit(Literal* node);
  Value visit(List* node);
  Value visit(Block* node);
  Value visit(IfExpression* node);
  Value visit(WhileExpression* node);
  Value visit(BinaryExpression* node);
  Value visit(Function* node);
  Value visit(CallExpression* node);
  Value visit(Identifier* node);
  Value visit(Declaration* node);

  Env* env;
};
#endif
