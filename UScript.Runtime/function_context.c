#include "function_context.h"
#include <stdlib.h>

USCRIPT_ERR create_basic_function_ctx(FunctionContext **ctx) {
	*ctx = (FunctionContext*)malloc(sizeof(FunctionContext));
	(*ctx)->arg_count = 0;
	eval_stack_create(&(*ctx)->eval_stack);

	return USCRIPT_ERR_SUCCESS;
}