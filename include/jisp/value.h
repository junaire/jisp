#ifndef JISP_VALUE_H_
#define JISP_VALUE_H_

#include <memory>
#include <string>
#include <vector>

#include "jisp/parser.h"
#include "jisp/types.h"

class Value {
 public:
  explicit Value(Types type) : type(type) {}
  virtual ~Value() = default;
  [[nodiscard]] Types getType() const { return type; }
  virtual void inspect() = 0;

 private:
  Types type;
};
#endif
