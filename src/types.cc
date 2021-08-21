#include "types.h"

void Sexpr::add(std::shared_ptr<BaseValue> val) {
  expr.push_back(std::move(val));
}