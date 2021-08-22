#include <gtest/gtest.h>

#include "lexer.h"
#include "tokenizer.h"
#include "types.h"
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
  std::string input{"(+ 12 ( -4 56777     "};
  Tokenizer tokenizer(input);
  auto tokens = tokenizer.tokenize();
  Lexer lexer{tokens};
  auto ast = lexer.parse();
  auto unit =
      dynamic_pointer_cast<Sexpr>(ast)->expr;
  EXPECT_EQ("+", dynamic_pointer_cast<Symbol>(unit[0])->getName());
  EXPECT_EQ("12", dynamic_pointer_cast<Literal>(unit[1])->getValue());
  auto level2 = dynamic_pointer_cast<Sexpr>(unit[2])->expr;
  EXPECT_EQ("-", dynamic_pointer_cast<Symbol>(level2[0])->getName());
  EXPECT_EQ("4", dynamic_pointer_cast<Literal>(level2[1])->getValue());
  EXPECT_EQ("56777", dynamic_pointer_cast<Literal>(level2[2])->getValue());
}
