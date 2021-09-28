#ifndef JISP_BUILTIN_H_
#define JISP_BUILTIN_H_

#include "jisp/env.h"
#include "jisp/value.h"

// Operators like + - * /
std::unique_ptr<Value> builtinOperators(Env& env, Value* vp, const char* op);

// builtin function print
std::unique_ptr<Value> builtinPrint(Env& env, Value* vp);

// builtin function define
std::unique_ptr<Value> builtinDefine(Env& env, Value* vp);
#endif
