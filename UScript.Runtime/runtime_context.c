#include "runtime_context.h"
#include <stdlib.h>

//! Creates a runtime context.
/*!
	\param[out] ctx The runtime context.
	\param[in] mdCtx The metadata context to use.
*/
USCRIPT_ERR create_runtime_ctx(UScriptRuntimeContext **ctx, UScriptMetadataContext *mdCtx) {
	*ctx = (UScriptRuntimeContext*)malloc(sizeof(UScriptRuntimeContext));
	(*ctx)->md_ctx = mdCtx;

	(*ctx)->frame_count = 1;
	(*ctx)->call_stack = (StackFrame**)malloc(sizeof(StackFrame*));

	(*ctx)->call_stack[0] = (StackFrame*)malloc(sizeof(StackFrame));
	(*ctx)->call_stack[0]->ip = 0;
	(*ctx)->cur_desc = (*ctx)->call_stack[0];

	// Create context for entry code
	__create_basic_function_ctx(&(*ctx)->call_stack[0]->func_ctx);

	return USCRIPT_ERR_SUCCESS;
}

//! Creates a stack frame.
/*!
	\param[in] ctx The runtime context.
	\param[out] frame The stack frame.
*/
USCRIPT_ERR create_stack_frame(UScriptRuntimeContext *ctx, StackFrame **frame) {
	*frame = (StackFrame*)malloc(sizeof(StackFrame));
	(*frame)->ip = 0;
	
	create_function_context(&(*frame)->func_ctx);

	return USCRIPT_ERR_SUCCESS;
}

//! Create and push a new stack frame.
/*!
	\param[in] ctx The runtime context to use.
*/
USCRIPT_ERR create_push_stack_frame(UScriptRuntimeContext *ctx) {
	StackFrame *frame;
	USCRIPT_ERR res;

	if((res = create_stack_frame(ctx, &frame)) != USCRIPT_ERR_SUCCESS) {
		return res;
	}

	ctx->call_stack[ctx->frame_count] = frame;
	ctx->cur_desc = ctx->call_stack[ctx->frame_count++];

	return USCRIPT_ERR_SUCCESS;
}

//! Helper method to get previous stack frame from a runtime context.
/*!
	\param[in] ctx The runtime context to use.
*/
StackFrame* stack_frame_get_previous(UScriptRuntimeContext *ctx) {
	if(ctx->frame_count == 1) {
		//TODO: error handling
	}

	return ctx->call_stack[ctx->frame_count - 2];
}
