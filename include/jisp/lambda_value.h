#ifndef JISP_LAMBDA_H_
#define JISP_LAMBDA_H_

#include <functional>
#include <memory>
#include <string>

#include "jisp/env.h"
#include "jisp/types.h"
#include "jisp/value.h"

class LambdaValue final : public Value {
 public:
  LambdaValue(std::unique_ptr<Value> f, std::unique_ptr<Value> b, Env* par)
      : formals(std::move(f)),
        body(std::move(b)),
        Value(ValueType::LAMBDA),
        env(par){};

  std::string inspect() override { return "<lambda>"; };
  std::unique_ptr<Value> accept(ASTVisitor& visitor) override;
  SexprValue* getFormals() { return formals->toSexpr(); }
  SexprValue* getBody() { return body->toSexpr(); }

  // FIXME: maybe we can use move or copy constructor
  std::unique_ptr<Value> moveFormals() { return std::move(formals); }
  std::unique_ptr<Value> moveBody() { return std::move(body); }
  void setFormals(std::string name, std::unique_ptr<Value> val) {
    env->set(std::move(name), std::move(val));
  }

 private:
  std::unique_ptr<Env> env;
  std::unique_ptr<Value> formals;
  std::unique_ptr<Value> body;
  // TODO(Jun): add an environment for our lambda value
};
#endif
