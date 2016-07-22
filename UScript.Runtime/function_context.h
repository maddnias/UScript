#ifndef FUNCTION_CONTEXT_H
#define FUNCTION_CONTEXT_H

#include "data_types.h"
#include <stdint.h>
#include "eval_stack.h"
#include "include/metadata.h"

typedef struct FunctionArgument {
	RuntimeObject obj;
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

//! Creates an empty function context.
USCRIPT_ERR function_context_create(FunctionContext **ctx);

//! Adds arguments to the selected function context from the selected evaluation stack.
USCRIPT_ERR populate_function_args(FunctionContext *ctx, EvalStack *stack, FunctionMetadataRow *row);
#endif