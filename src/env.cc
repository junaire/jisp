#include "jisp/env.h"

#include "jisp/ast/ast.h"
#include "jisp/ast/builtin.h"

void Env::set(const std::string& name, ASTNode* val) {
  environment.insert_or_assign(name, val);
}

ASTNode* Env::get(const std::string& name) {
  auto result = environment.find(name);
  if (result != environment.end()) {
    return result->second;
  }
  if (parent != nullptr) {
    if (auto* res = parent->get(name)) {
      return res;
    }
  }

  fmt::print("Unbound symbol {}\n", name);
  assert(false);
  // TODO(Jun): If we can't find the symbol, we should throw an error:
  // Unbound symbol
}

// Debug popurse
void Env::dump() {
  for (const auto& ele : environment) {
    fmt::print("{} => ", ele.first);
    ele.second->dump(0);
  }
}

void Env::setParent(Env* par) { parent = par; }
