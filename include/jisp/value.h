#ifndef JISP_VALUE_H_
#define JISP_VALUE_H_

#include <memory>
#include <string>
#include <vector>

#include "jisp/types.h"

class NumberValue;

class Value {
 public:
  Value(Types type) : type(type) {}
  virtual ~Value() = default;
  Types getType() const { return type; }
  virtual void inspect() = 0;
  // std::unique_ptr<NumberValue> toNumberValue() {
  // return std::dynamic_cast<NumberValue*>(this);
  //}

 private:
  Types type;
};
#endif
