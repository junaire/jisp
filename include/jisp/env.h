#ifndef JISP_ENV_H_
#define JISP_ENV_H_

#include <fmt/format.h>

#include <cassert>
#include <memory>
#include <string>
#include <unordered_map>

class ASTNode;

class Env {
 public:
  explicit Env(Env* par) : parent(par){};

  Env() = default;
  ~Env() = default;

  Env(const Env&) = delete;
  Env& operator=(const Env&) = delete;
  Env(Env&&) = delete;
  Env& operator=(Env&&) = delete;

  void set(const std::string& name, ASTNode* val);

  ASTNode* get(const std::string& name);

  void dump();

  void setParent(Env* par);

 private:
  std::unordered_map<std::string, ASTNode*> environment;
  Env* parent = nullptr;
};

#endif
