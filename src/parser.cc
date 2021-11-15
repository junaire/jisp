#include "jisp/parser/parser.h"

#include <cassert>

#include "jisp/ast/ast.h"
#include "jisp/ast/builtin.h"

const Token& Parser::currentToken() const { return tokens.at(index); }

Token Parser::getToken() { return tokens.at(index++); }

void Parser::advance() {
  if (index < tokens.size()) {
    ++index;
  }
}

bool Parser::isEnd() const { return index == tokens.size(); }

bool Parser::isCallExpr() const {
  return funcTbl.contains(currentToken().getValue());
}

std::unique_ptr<ASTNode> Parser::parseBlock(bool keepSingleNode) {
  // skip `(`
  advance();

  if (isCallExpr()) {
    auto node = parseCallExpression();
    advance();
    return node;
  }

  auto block = std::make_unique<Block>();

  while (currentToken().isNot(Token::Kind::RightParen)) {
    block->append(parseNode());
  }

  // eat `)`
  advance();

  if (keepSingleNode) {
    // If there is only one element in the list,
    // return it without block
    if (block->size() == 1) {
      return block->drop();
    }
  }
  return block;
}

std::unique_ptr<ASTNode> Parser::parseList() {
  // skip `[`
  advance();

  auto list = std::make_unique<List>();

  while (currentToken().isNot(Token::Kind::RightSquare)) {
    list->append(parseNode());
  }

  // eat `]`
  advance();

  return list;
}

std::unique_ptr<ASTNode> Parser::parseFunction() {
  assert(currentToken().is(Token::Kind::Function));

  advance();
  auto fnName = getToken().getValue();

  auto callee = std::make_unique<Identifier>(fnName);
  auto args = parseList();
  auto body = parseBlock(false);

  auto func = std::make_unique<Function>(std::move(callee), std::move(args),
                                         std::move(body));

  // store function names, so we can parse CallExpression
  funcTbl.emplace(fnName);
  return func;
}

std::unique_ptr<ASTNode> Parser::parseDeclaretion() {
  assert(currentToken().is(Token::Kind::Define));

  advance();
  auto id = parseNode();
  auto init = parseNode();

  return std::make_unique<Declaretion>(std::move(id), std::move(init));
}

std::unique_ptr<ASTNode> Parser::parseBinaryExpression() {
  auto op = parseBuiltin();
  auto lhs = parseNode();
  auto rhs = parseNode();

  return std::make_unique<BinaryExpression>(std::move(op), std::move(lhs),
                                            std::move(rhs));
}

std::unique_ptr<ASTNode> Parser::parseIfExpression() {
  assert(currentToken().getKind() == Token::Kind::If);
  advance();
  auto test = parseBlock(false);
  auto consequent = parseBlock(false);
  auto alternate = parseBlock(false);

  return std::make_unique<IfExpression>(std::move(test), std::move(consequent),
                                        std::move(alternate));
}

std::unique_ptr<ASTNode> Parser::parseWhileExpression() {
  assert(currentToken().getKind() == Token::Kind::While);
  advance();
  auto test = parseBlock(false);
  auto body = parseBlock(false);

  return std::make_unique<WhileExpression>(std::move(test), std::move(body));
}

std::unique_ptr<ASTNode> Parser::parseCallExpression() {
  auto callee = std::make_unique<Identifier>(getToken().getValue());
  auto args = parseBlock(false);
  return std::make_unique<CallExpression>(std::move(callee), std::move(args));
}

// `parseNode()` is not responsible for advance the token
std::unique_ptr<ASTNode> Parser::parseNode() {
  switch (currentToken().getKind()) {
    case Token::Kind::Integer:
      return std::make_unique<Literal>(std::stoi(getToken().getValue()));
    case Token::Kind::String:
      return std::make_unique<Literal>(getToken().getValue());
    case Token::Kind::Identifier:
      return std::make_unique<Identifier>(getToken().getValue());

    case Token::Kind::Plus:
    case Token::Kind::Minus:
    case Token::Kind::Multiply:
    case Token::Kind::Divide:
      return parseBinaryExpression();

    case Token::Kind::Define:
      return parseDeclaretion();
    case Token::Kind::Function:
      return parseFunction();
    case Token::Kind::If:
      return parseIfExpression();
    case Token::Kind::While:
      return parseWhileExpression();

    case Token::Kind::LeftParen:
      return parseBlock();
    case Token::Kind::LeftSquare:
      return parseList();
  }
  return nullptr;
}

std::unique_ptr<Builtin> Parser::parseBuiltin() {
  switch (getToken().getKind()) {
    case Token::Kind::Plus:
      return std::make_unique<Add>();
    case Token::Kind::Minus:
      return std::make_unique<Sub>();
    case Token::Kind::Multiply:
      return std::make_unique<Multiply>();
    case Token::Kind::Divide:
      return std::make_unique<Divide>();
    default:
      assert(false);
  }
}

std::unique_ptr<ASTNode> Parser::parse() {
  // So that we can have more complex program
  auto program = std::make_unique<Block>();
  while (!isEnd()) {
    program->append(parseNode());
  }
  return program;
}
