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
	UScriptTypeDesc return_type_desc;
	int32_t arg_count;
	FunctionArgument **args;
	EvalStack *eval_stack;
} FunctionContext;

//! Creates a basic function context.
USCRIPT_ERR __create_basic_function_ctx(FunctionContext **ctx);
#endif