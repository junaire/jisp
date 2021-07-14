#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "mpc.h"

#define LASSERT(args, cond, fmt, ...) \
	if (!(cond)) { lval* err = lval_err(fmt, ##__VA_ARGS__); lval_del(args); return err; }
#define LASSERT_TYPE(func, args, index, expect) \
	LASSERT(args, args->cell[index]->type == expect, \
			"Function '%s' passed incorrect type for argument %i. " \
			"Got %s, Expected %s.", \
			func, index, ltype_name(args->cell[index]->type), ltype_name(expect))

#define LASSERT_NUM(func, args, num) \
	LASSERT(args, args->count == num, \
			"Function '%s' passed incorrect number of arguments. " \
			"Got %i, Expected %i.", \
			func, args->count, num)

#define LASSERT_NOT_EMPTY(func, args, index) \
	LASSERT(args, args->cell[index]->count != 0, \
			"Function '%s' passed {} for argument %i.", func, index);
enum {
	LERR_DIV_ZERO,
	LERR_BAD_OP,
	LERR_BAD_NUM
};

enum {
	LVAL_NUM,
	LVAL_ERR,
	LVAL_SYM,
	LVAL_FUN,
	LVAL_SEXPR,
	LVAL_QEXPR
};

char* ltype_name(int t) {
	switch(t) {
		case LVAL_FUN: return "Function";
		case LVAL_NUM: return "Number";
		case LVAL_ERR: return "Error";
		case LVAL_SYM: return "Symbol";
		case LVAL_SEXPR: return "S-Expression";
		case LVAL_QEXPR: return "Q-Expression";
		default: return "Unknown";
	}
}
struct lval;
typedef struct lval lval;
typedef struct lenv lenv;
typedef lval*(*lbuiltin)(lenv*, lval*);


struct lval{
	int type;
	long num;
	char* err;
	char* sym;
	lbuiltin builtin;
	lenv* env;
	lval* formals;
	lval* body;

	int count;
	struct lval** cell;
};

struct lenv{
	lenv* par;
	int count;
	char** syms;
	lval** vals;
};

lval* lval_num(long x)
{
	lval* v = (lval*)malloc(sizeof(lval));
	v->type = LVAL_NUM;
	v->num = x;
	return v;
}

lval* lval_err(char* fmt, ...) {
	lval* v = malloc(sizeof(lval));
	v->type = LVAL_ERR;  
	va_list va;
	va_start(va, fmt);  
	v->err = malloc(512);  
	vsnprintf(v->err, 511, fmt, va);  
	v->err = realloc(v->err, strlen(v->err)+1);
	va_end(va);  
	return v;
}

lval* lval_sym(char* s)
{
	lval* v = (lval*)malloc(sizeof(lval));
	v->type = LVAL_SYM;
	v->sym = malloc(strlen(s) + 1);
	strcpy(v->sym, s);
	return v;
}

lval* lval_sexpr()
{
	lval* v = (lval*)malloc(sizeof(lval));
	v->type = LVAL_SEXPR;
	v->count = 0;
	v->cell = NULL;
	return v;
}

lval* lval_qexpr()
{
	lval* v = (lval*)malloc(sizeof(lval));
	v->type = LVAL_QEXPR;
	v->count = 0;
	v->cell = NULL;
	return v;
}

lval* lval_fun(lbuiltin func)
{
	lval* v = (lval*)malloc(sizeof(lval));
	v->type = LVAL_FUN;
	v->builtin = func;
	return v;
}

lenv* lenv_new();
lval* lval_lambda(lval* formals, lval* body)
{
	lval* v = (lval*)malloc(sizeof(lval));
	v->type = LVAL_FUN;
	v->builtin = NULL;
	v->env = lenv_new();
	v->formals = formals;
	v->body = body;
	return v;
}

void lenv_del(lenv*);
void lval_del(lval* v)
{
	switch (v->type) {
		case LVAL_FUN:
			if (!v->builtin) {
				lenv_del(v->env);
				lval_del(v->formals);
				lval_del(v->body);
			}
		case LVAL_NUM:
			break;
		case LVAL_ERR:
			free(v->err);
			break;
		case LVAL_SYM:
			free(v->sym);
			break;
		case LVAL_QEXPR:
		case LVAL_SEXPR:
			for (int i = 0; i < v->count; i++) {
				lval_del(v->cell[i]);
			}
			free(v->cell);
			break;
	}
	free(v);
}

lval* lval_copy(lval* v);
lenv* lenv_copy(lenv* e)
{
	lenv* n = (lenv*)malloc(sizeof(lenv));
	n->par = e->par;
	n->count = e->count;
	n->syms = malloc(sizeof(char*) * e->count);
	n->vals = malloc(sizeof(lval*) * e->count);
	for (int i = 0; i < e->count; i++) {
		strcpy(n->syms[i], e->syms[i]);
		n->vals[i] = lval_copy(e->vals[i]);

	}
	return n;
}

lval* lval_copy(lval* v)
{
	lval* x = (lval*)malloc(sizeof(lval));
	x->type = v->type;
	switch (v->type) {
		case LVAL_FUN:
			if (v->builtin) {
				x->builtin = v->builtin;
			}else {
				x->builtin = NULL;
				x->env = lenv_copy(v->env);
				x->formals = lval_copy(v->formals);
				x->body = lval_copy(v->body);
			}
			break;
		case LVAL_NUM:
			x->num = v->num;
			break;
		case LVAL_SYM:
			x->sym = malloc(strlen(v->sym) + 1);
			strcpy(x->sym, v->sym);
			break;
		case LVAL_ERR:
			x->err = malloc(strlen(v->err) + 1);
			strcpy(x->err, v->err);
			break;
		case LVAL_SEXPR:
		case LVAL_QEXPR:
			x->count = v->count;
			x->cell = malloc(sizeof(lval*) * v->count);
			for (int i = 0; i < x->count; i++) {
				x->cell[i] = v->cell[i];
			}
			break;
	}
	return x;
}

lenv* lenv_new()
{
	lenv* e = (lenv*)malloc(sizeof(lenv));
	e->par =NULL;
	e->count = 0;
	e->syms = NULL;
	e->vals = NULL;
	return e;
}

void lenv_del(lenv* e)
{
	for (int i = 0 ; i < e->count; i++) {
		free(e->syms[i]);
		lval_del(e->vals[i]);
	}
	free(e->syms);
	free(e->vals);
	free(e);
}

void lenv_put(lenv*, lval*, lval*);
void lenv_def(lenv* e, lval* k, lval* v)
{
	//interate unitl no parent
	while(e->par) {
		e = e->par;
	}
	//define a variable in the global env
	lenv_put(e, k, v);
}
lval* lenv_get(lenv* e, lval* k)
{
	//在lenv中通过变量名找lval，返回一个copy
	for (int i= 0 ;	i < e->count; i++) {
		if (strcmp(e->syms[i], k->sym) == 0) {
			return lval_copy(e->vals[i]);
		}
	}

	//在父级环境中寻找变量，这使我们可以在函数中使用全局变量。
	if (e->par) {
		return lenv_get(e->par, k);
	}else {
		return lval_err("unbound symbol!");
	}
}

void lenv_put(lenv* e, lval* k, lval* v)
{
	//有同名的变量，改变他的值。
	for (int i = 0; i < e->count; i++) {
		if (strcmp(e->syms[i], k->sym) == 0) {
			lval_del(e->vals[i]);
			e->vals[i] = lval_copy(v);
			return;
		}
	}

	//否则，递增cell的数量，
	//并把此lval加进去
	e->count++;
	e->vals = realloc(e->vals, sizeof(lval) * e->count);
	e->syms = realloc(e->syms, sizeof(char*) * e->count);
	e->vals[e->count - 1] = lval_copy(v);
	e->syms[e->count - 1]  = malloc(strlen(k->sym) + 1);
	strcpy(e->syms[e->count - 1], k->sym);
}
void lval_print(lval*);
void lval_expr_print(lval* v, char open, char close)
{
	putchar(open);
	for (int i = 0; i < v->count; i++) {
		lval_print(v->cell[i]);

		if (i != v->count - 1)
			putchar(' ');
	}
	putchar(close);

}

void lval_print(lval* v)
{
	switch(v->type) {
		case LVAL_NUM:
			printf("%li",v->num);
			break;
		case LVAL_ERR:
			printf("Error: %s", v->err);
			break;
		case LVAL_SYM:
			printf("%s", v->sym);
			break;
		case LVAL_SEXPR:
			lval_expr_print(v, '(',')');
			break;
		case LVAL_QEXPR:
			lval_expr_print(v, '{','}');
			break;
		case LVAL_FUN:
			if (v->builtin) {
				printf("<builtin funciton>");
			}else {
				printf("(\\ ");
				lval_print(v->formals);
				puts(" ");
				lval_print(v->body);
				puts(" )");
			}
			break;
	}
}

void lval_println(lval* v)
{
	lval_print(v);
	putchar('\n');
}

lval* lval_add(lval* v, lval* x)
{
	//cell是一个lval数组，储存了所有元素
	//全部加到cell中，变成一个S-Expression
	v->count++;
	v->cell = realloc(v->cell, sizeof(lval*) * v->count);
	v->cell[v->count - 1] = x;
	return v;
}

lval* lval_read_num(mpc_ast_t* t) {
	errno = 0;
	long x = strtol(t->contents, NULL, 10);
	return errno != ERANGE 
		? lval_num(x)
		: lval_err("invalid number!");
}

lval* lval_read(mpc_ast_t* t) 
	//创建了一个lval，把所有的元素都加到了他的cell中
{
	//if it's type is number, parse it directly
	if (strstr(t->tag, "number")) {
		return lval_read_num(t);
	}
	//if it is a symbol, parse it as a symbol
	if (strstr(t->tag, "symbol")) {
		return lval_sym(t->contents);
	}

	lval* x = NULL;

	if (strcmp(t->tag, ">") == 0) {
		//初始化
		x = lval_sexpr();
	}
	if(strstr(t->tag, "sexpr")) {
		x = lval_sexpr();
	}
	if(strstr(t->tag, "qexpr")) {
		x = lval_qexpr();
	}

	for (int i = 0; i < t->children_num; i++) {
		if (strcmp(t->children[i]->contents, "(") == 0)
			continue;
		if (strcmp(t->children[i]->contents, ")") == 0) 
			continue;
		if (strcmp(t->children[i]->contents, "{") == 0)
			continue;
		if (strcmp(t->children[i]->contents, "}") == 0) 
			continue;
		if (strcmp(t->children[i]->tag, "regex") == 0) 
			continue;
		//遍历字节点，递归添加
		x = lval_add(x, lval_read(t->children[i]));
	}
	return x;
}


lval* lval_pop(lval* v, int i)
{
	lval* x = v->cell[i];
	/* Shift memory after the item at "i" over the top */
	memmove(&v->cell[i], &v->cell[i+1],
			sizeof(lval*) * (v->count-i-1));

	/* Decrease the count of items in the list */
	v->count--;

	/* Reallocate the memory used */
	v->cell = realloc(v->cell, sizeof(lval*) * v->count);
	return x;
}

lval* lval_take(lval* v, int i)
{
	lval* x = lval_pop(v, i);
	lval_del(v);
	return x;
}

lval* builtin_op(lenv* e, lval* a, char* op)
{
	lval* x = lval_pop(a, 0);	

	if (strcmp(op, "-") && a->count == 0)
		x->num = -(x->num);

	while(a->count > 0) {
		lval* y = lval_pop(a, 0);

		if (strcmp(op, "+") == 0)
			x->num += y->num;
		if (strcmp(op, "-") == 0)
			x->num -= y->num;
		if (strcmp(op, "*") == 0)
			x->num *= y->num;
		if (strcmp(op, "/") == 0) {
			if (y->num == 0) {
				lval_del(x);
				lval_del(y);
				return lval_err("Division by zero");
			}
			x->num /= y->num;
			break;
		}
		lval_del(y);
	}
	lval_del(a);
	return x;
}


lval* builtin_head(lenv* e, lval* a)
{
	LASSERT_NUM("head", a, 1);
	LASSERT_TYPE("head", a, 0, LVAL_QEXPR);
	LASSERT_NOT_EMPTY("head", a, 0);
	lval* v = lval_take(a, 0);
	while(a->count > 0) {
		lval_del(lval_pop(v ,1));
	}
	return v;
}

lval* builtin_tail(lenv* e, lval* a)
{
	LASSERT_NUM("tail", a, 1);
	LASSERT_TYPE("tail", a, 0, LVAL_QEXPR);
	LASSERT_NOT_EMPTY("tail", a, 0);
	lval* v = lval_take(a, 0);
	lval_del(lval_pop(v ,0));
	return v;
}

lval* builtin_list(lenv* e, lval* a)
{
	a->type = LVAL_QEXPR;
	return a;
}

lval* lval_eval(lenv* e, lval*);
lval* builtin_eval(lenv* e, lval* a)
{
	LASSERT(a, a->count == 1,
			"Too much arguments!"
		   );
	LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
			"arguments type error!"
		   );
	lval* x = lval_take(a, 0);
	x->type = LVAL_SEXPR;
	return lval_eval(e, x);
}
lval* builtin_add(lenv* e, lval* v)
{
	return builtin_op(e,v,"+");
}


lval* builtin_sub(lenv* e, lval* v)
{
	return builtin_op(e,v,"-");
}
lval* builtin_mul(lenv* e, lval* v)
{
	return builtin_op(e,v,"*");
}
lval* builtin_div(lenv* e, lval* v)
{
	return builtin_op(e,v,"/");
}

lval* builtin_var(lenv* e, lval* a, char* func)
{
	LASSERT_TYPE(func, a, 0, LVAL_QEXPR);

	lval* syms = a->cell[0];
	for (int i = 0; i < syms->count; i++) {
		LASSERT(a, (syms->cell[i]->type == LVAL_SYM),
				"Function '%s' cannot define non-symbol. "
				"Got %s, Expected %s.", func, 
				ltype_name(syms->cell[i]->type), ltype_name(LVAL_SYM));
	}

	LASSERT(a, (syms->count == a->count-1),
			"Function '%s' passed too many arguments for symbols. "
			"Got %i, Expected %i.", func, syms->count, a->count-1);

	for (int i = 0; i < syms->count; i++) {
		if (strcmp(func, "def") == 0) {
			lenv_def(e, syms->cell[i], a->cell[i + 1]);
		}
		if (strcmp(func, "=") == 0) {
			lenv_put(e, syms->cell[i], a->cell[i + 1]);
		}
	}
	lval_del(a);
	return lval_sexpr();
}

lval* builtin_lambda(lenv* e, lval* a)
{
	/* Check Two arguments, each of which are Q-Expressions */
	LASSERT_NUM("\\", a, 2);
	LASSERT_TYPE("\\", a, 0, LVAL_QEXPR);
	LASSERT_TYPE("\\", a, 1, LVAL_QEXPR);
	/* Check first Q-Expression contains only Symbols */
	for (int i = 0; i < a->cell[0]->count; i++) {
		LASSERT(a, (a->cell[0]->cell[i]->type == LVAL_SYM),
				"Cannot define non-symbol. Got %s, Expected %s.",
				ltype_name(a->cell[0]->cell[i]->type),ltype_name(LVAL_SYM));
	}
	lval* formals = lval_pop(a,0);
	lval* body = lval_pop(a,0);
	lval_del(a);
	return lval_lambda(formals, body);
}

lval* builtin_put(lenv* e, lval* a)
{
	return builtin_var(e, a, "=");
}

lval* builtin_def(lenv* e, lval* a)
{
	return builtin_var(e,a,"def");
}
void lenv_add_builtin(lenv* e, char* name, lbuiltin func)
{
	lval* a = lval_sym(name);
	lval* v = lval_fun(func);
	lenv_put(e,a,v);
	lval_del(a);
	lval_del(v);
}

void lenv_add_builtins(lenv* e)
{
	lenv_add_builtin(e,"list",builtin_list);
	lenv_add_builtin(e,"head",builtin_head);
	lenv_add_builtin(e,"tail",builtin_tail);
	lenv_add_builtin(e,"eval",builtin_eval);
	lenv_add_builtin(e,"+",builtin_add);
	lenv_add_builtin(e,"-",builtin_sub);
	lenv_add_builtin(e,"*",builtin_mul);
	lenv_add_builtin(e,"/",builtin_div);
	lenv_add_builtin(e,"def",builtin_def);
	lenv_add_builtin(e,"\\",builtin_lambda);
	lenv_add_builtin(e,"=",builtin_put);
}

lval* lval_call(lenv* e, lval* f, lval* a) {

	/* If Builtin then simply apply that */
	if (f->builtin) { return f->builtin(e, a); }


	/* While arguments still remain to be processed */
	while (a->count) {

		/* If we've ran out of formal arguments to bind */
		if (f->formals->count == 0) {
			lval_del(a);
			return lval_err("Function passed too many arguments. "
					"Got %i, Expected %i."); 
		}

		/* Pop the first symbol from the formals */
		lval* sym = lval_pop(f->formals, 0);

		/* Special Case to deal with '&' */
		if (strcmp(sym->sym, "&") == 0) {

			/* Ensure '&' is followed by another symbol */
			if (f->formals->count != 1) {
				lval_del(a);
				return lval_err("Function format invalid. "
						"Symbol '&' not followed by single symbol.");
			}

			/* Next formal should be bound to remaining arguments */
			lval* nsym = lval_pop(f->formals, 0);
			lenv_put(f->env, nsym, builtin_list(e, a));
			lval_del(sym); lval_del(nsym);
			break;
		}

		/* Pop the next argument from the list */
		lval* val = lval_pop(a, 0);

		/* Bind a copy into the function's environment */
		lenv_put(f->env, sym, val);

		/* Delete symbol and value */
		lval_del(sym); lval_del(val);
	}

	/* Argument list is now bound so can be cleaned up */
	lval_del(a);

	/* If '&' remains in formal list bind to empty list */
	if (f->formals->count > 0 &&
			strcmp(f->formals->cell[0]->sym, "&") == 0) {

		/* Check to ensure that & is not passed invalidly. */
		if (f->formals->count != 2) {
			return lval_err("Function format invalid. "
					"Symbol '&' not followed by single symbol.");
		}

		/* Pop and delete '&' symbol */
		lval_del(lval_pop(f->formals, 0));

		/* Pop next symbol and create empty list */
		lval* sym = lval_pop(f->formals, 0);
		lval* val = lval_qexpr();

		/* Bind to environment and delete */
		lenv_put(f->env, sym, val);
		lval_del(sym); lval_del(val);
	}

	/* If all formals have been bound evaluate */
	if (f->formals->count == 0) {

		/* Set environment parent to evaluation environment */
		f->env->par = e;

		/* Evaluate and return */
		return builtin_eval(f->env, 
				lval_add(lval_sexpr(), lval_copy(f->body)));
	} else {
		/* Otherwise return partially evaluated function */
		return lval_copy(f);
	}

}
lval* lval_eval_sexpr(lenv* e, lval* v)
{
	for (int i = 0; i < v->count; i++) {
		v->cell[i] = lval_eval(e, v->cell[i]);
	}
	for (int i = 0; i < v->count; i++) {
		//去除所有error类型的lval
		if (v->cell[i]->type == LVAL_ERR)
			return lval_take(v, i);
	}

	if (v->count == 0)
		return v;
	if (v->count == 1)
		return lval_take(v, 0);

	lval* f = lval_pop(v, 0);
	if (f->type != LVAL_FUN) {
		lval_del(f);
		lval_del(v);
		return lval_err("first element is not a function!");
	}
	//core logic
	lval* res = lval_call(e, f, v);
	lval_del(f);
	return res;

}


lval* lval_eval(lenv* e, lval* v)
{
	if ((v->type) == LVAL_SYM) {
		//如果是symbol，先尝试在环境中寻找，并返回一份copy
		lval* x = lenv_get(e,v);
		lval_del(v);
		return x;
	}
	if (v->type == LVAL_SEXPR)
		//如果是S-Expression，call this.
		return lval_eval_sexpr(e, v);
	return v;
}

int main(int argc, char** argv)
{
	mpc_parser_t* Number = mpc_new("number");
	mpc_parser_t* Symbol = mpc_new("symbol");
	mpc_parser_t* Sexpr = mpc_new("sexpr");
	mpc_parser_t* Qexpr = mpc_new("qexpr");
	mpc_parser_t* Expr = mpc_new("expr");
	mpc_parser_t* Lispy = mpc_new("lispy");

	mpca_lang(MPCA_LANG_DEFAULT,
			"                                          \
			number : /-?[0-9]+/ ;                      \
			symbol :/[a-zA-Z0-9_+\\-*\\/\\\\=<>!&]+/ ; \
			sexpr  : '(' <expr>* ')' ;                 \
			qexpr  : '{' <expr>* '}' ;                 \
			expr   : <number> | <symbol> | <sexpr> | <qexpr>; \
			lispy  : /^/ <expr>* /$/ ;               \
			",
			Number, Symbol, Sexpr, Qexpr, Expr, Lispy);

	puts("Jun's Lisp Version 0.0.3\n");
	puts("Press Ctrl-C to exit...\n");

	lenv* e = lenv_new();
	lenv_add_builtins(e);
	while(1) {
		char* input = readline("jisp> ");
		add_history(input);
		mpc_result_t r;
		if(mpc_parse("<stdin>", input, Lispy, &r)) {
			lval* result = lval_eval(e, lval_read(r.output));
			lval_println(result);
			lval_del(result);
			mpc_ast_delete(r.output);
		}else{
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
		free(input);
	}

	mpc_cleanup(6, Number, Symbol, Sexpr, Qexpr, Expr, Lispy);

	return 0;
}
