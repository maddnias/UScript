#include "function_context.h"
#include <stdlib.h>
#include "include/metadata.h"
#include <memory.h>
#include "mem_manager.h"

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
USCRIPT_ERR function_context_create(FunctionContext **ctx) {
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
		ctx->args[i]->obj.desc = *row->param_descriptors[i];

		int32_t typeSize = uscript_type_size(ctx->args[i]->obj.desc.type);

		StackEntry *entry;
		if(eval_stack_pop(stack, &entry) != USCRIPT_ERR_SUCCESS) {
			//TODO: error handling	
		}

		if (typeSize == 0 /* RUNTIME_DETERMINED */) {
			typeSize = uscript_type_size(entry->obj->desc.type);
			ctx->args[i]->obj.desc.type = entry->obj->desc.type;
		}

		ctx->args[i]->obj.data = (char*)malloc(typeSize);
		memcpy(ctx->args[i]->obj.data, entry->obj->data, typeSize);
		//stack_entry_destroy(entry);
	}

	// Reverse arguments for correct popping order
	for (int i = 0; i < ctx->arg_count / 2; i++) {
		FunctionArgument *tmp = ctx->args[i];
		ctx->args[i] = ctx->args[ctx->arg_count - (i + 1)];
		ctx->args[ctx->arg_count - (i + 1)] = tmp;
	}

	return USCRIPT_ERR_SUCCESS;
}
