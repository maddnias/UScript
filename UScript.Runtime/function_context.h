#ifndef FUNCTION_CONTEXT_H
#define FUNCTION_CONTEXT_H

#include "data_types.h"
#include <stdint.h>
#include "eval_stack.h"

typedef struct FunctionArgument {
	UScriptTypeDesc type_desc;
	int32_t idx;
} FunctionArgument;

typedef struct FunctionContext {
	int32_t arg_count;
	FunctionArgument **args;
	EvalStack *eval_stack;
} FunctionContext;


USCRIPT_ERR create_basic_function_ctx(FunctionContext **ctx);
#endif