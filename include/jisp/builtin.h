#ifndef JISP_BUILTIN_H_
#define JISP_BUILTIN_H_
#include "jisp/env.h"
#include "jisp/function_value.h"
#include "jisp/value.h"

ValuePtr builtinOperators(Env& env, const ValuePtr& vp, const char* op);

ValuePtr add_builtin(const BuiltinFunction& func);

void add_builtins(Env& env);
#endif
