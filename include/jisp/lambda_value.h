#ifndef JISP_LAMBDA_H_
#define JISP_LAMBDA_H_

#include <functional>
#include <memory>
#include <string>

#include "jisp/value.h"

class LambdaValue : public Value {
 public:
  LambdaValue() : Value(Types::LAMBDA) {}
};
#endif
