#include "function_context.h"
#include <stdlib.h>

//! Creates a basic function context.
/*!
	\param[out] ctx The function context.
	\remark This is used to create the first function context required for execution.
*/
USCRIPT_ERR __create_basic_function_ctx(FunctionContext **ctx) {
	*ctx = (FunctionContext*)malloc(sizeof(FunctionContext));
	(*ctx)->arg_count = 0;
	eval_stack_create(&(*ctx)->eval_stack);

	return USCRIPT_ERR_SUCCESS;
}