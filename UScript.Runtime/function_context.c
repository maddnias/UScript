#include "function_context.h"
#include <stdlib.h>
#include "include/metadata.h"
#include <memory.h>

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

//! Creates an empty function context.
/*!
	\param[in] ctx The function context.
*/
USCRIPT_ERR create_function_context(FunctionContext **ctx) {
	*ctx = (FunctionContext*)malloc(sizeof(FunctionContext));
	(*ctx)->arg_count = 0;
	eval_stack_create(&(*ctx)->eval_stack);

	return USCRIPT_ERR_SUCCESS;
}

//! Adds arguments to the selected function context from the selected evaluation stack.
/*!
	\param[in] ctx The function context.
	\param[in] stack The evaluation stack to pop from.
	\param[in] row The callee function metadata row.
*/
USCRIPT_ERR populate_function_args(FunctionContext* ctx, EvalStack* stack, FunctionMetadataRow *row) {
	ctx->arg_count = row->param_count;
	ctx->args = (FunctionArgument**)malloc(ctx->arg_count * sizeof(FunctionArgument*));

	for(int i = 0;i < ctx->arg_count;i++) {
		ctx->args[i] = (FunctionArgument*)malloc(sizeof(FunctionArgument));
		ctx->args[i]->idx = i;
		ctx->args[i]->type_desc = *row->param_descriptors[i];

		int32_t typeSize = uscript_type_size(ctx->args[i]->type_desc.type);

		StackEntry *entry = eval_stack_pop(stack);
		if (typeSize == 0 /* RUNTIME_DETERMINED */) {
			typeSize = uscript_type_size(entry->type_desc->type);
			ctx->args[i]->type_desc.type = entry->type_desc->type;
		}

		ctx->args[i]->type_desc.data = (char*)malloc(typeSize);
		memcpy(ctx->args[i]->type_desc.data, entry->type_desc->data, typeSize);
	}

	return USCRIPT_ERR_SUCCESS;
}
