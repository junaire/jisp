#include <gtest/gtest.h>

#include "lexer.h"
#include "tokenizer.h"

TEST(JispTest, TokenizerTest) {
  std::string input{"(+ 12 4)"};
  Tokenizer tokenizer(input);
  auto tokens = tokenizer.tokenize();
  EXPECT_EQ("(", tokens[0]);
  EXPECT_EQ("+", tokens[1]);
  EXPECT_EQ("12", tokens[2]);
  EXPECT_EQ("4", tokens[3]);
  EXPECT_EQ(")", tokens[4]);
}

TEST(JispTest, LexerTest) {
  std::string input{"0"};
  Tokenizer tokenizer(input);
  auto tokens = tokenizer.tokenize();
  Lexer lexer{tokens};
  auto ast = lexer.parse();
  EXPECT_EQ("0", ast->getName());
}
