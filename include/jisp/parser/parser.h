#ifndef JISP_PARSER_H_
#define JISP_PARSER_H_

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "jisp/ast/ast.h"
#include "jisp/lexer/token.h"

using Tokens = std::vector<Token>;

class Parser {
 public:
  explicit Parser(Tokens tokens) : tokens(std::move(tokens)), index(0) {}
  std::unique_ptr<ASTNode> parse();

 private:
  std::unique_ptr<ASTNode> parseNode();

  std::unique_ptr<ASTNode> parseBlock(bool keepSingleNode = true);

  std::unique_ptr<ASTNode> parseList();

  std::unique_ptr<ASTNode> parseIdentifier();

  std::unique_ptr<ASTNode> parseFunction();

  std::unique_ptr<ASTNode> parseDeclaretion();

  std::unique_ptr<ASTNode> parseCallExpression();

  std::unique_ptr<ASTNode> parseIfExpression();

  std::unique_ptr<ASTNode> parseWhileExpression();

  std::unique_ptr<ASTNode> parseBinaryExpression();

  std::unique_ptr<Builtin> parseBuiltin();

  [[nodiscard]] bool isCallExpr() const;

  const Token& currentToken() const;

  void advance();

  Token getToken();

  [[nodiscard]] bool isEnd() const;

  Tokens tokens;
  size_t index;
  std::unordered_set<std::string> funcTbl;
};
#endif
