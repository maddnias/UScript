#include "opcodes.h"
#include "metadata.h"
#include "runtime_context.h"
#include "include/executor.h"
#include <memory.h>

//! Executes a LI32 instruction from the current IP.
/*!
	\param[in] ctx The current runtime context.
	\param[in] instr The instruction to execute.
*/
void instr_execute_li32(UScriptRuntimeContext *ctx, UScriptInstruction *instr) {
	StackEntry *entry;
	stack_entry_create(&entry, I32);

	*(int32_t*)entry->obj->data = *(int32_t*)instr->operand;

	// TODO: error handling
	if (eval_stack_push(ctx->cur_frame->func_ctx->eval_stack, entry) != USCRIPT_ERR_SUCCESS) {
		return;
	}
}

//! Executes a SCALL instruction from the current IP.
/*!
	\param[in] ctx The current runtime context.
	\param[in] instr The instruction to execute.
*/
void instr_execute_scall(UScriptRuntimeContext *ctx, UScriptInstruction *instr) {
	FunctionMetadataRow *funcRow;

	if (resolve_func_token(&funcRow, ctx->md_ctx,
		*(int32_t*)instr->operand) != USCRIPT_ERR_SUCCESS) {
		//TODO: error handling
		return;
	}

	if(stack_frame_create_push(ctx) != USCRIPT_ERR_SUCCESS) {
		//TODO: error handling
		return;
	}

	StackFrame *previousFrame = stack_frame_get_previous(ctx);

	populate_function_args(ctx->cur_frame->func_ctx, previousFrame->func_ctx->eval_stack,
		funcRow);

	ctx->cur_frame->ip = funcRow->code_relative_addr;
}

//! Executes a LPARAM instruction from the current IP.
/*!
	\param[in] ctx The current runtime context.
	\param[in] instr The instruction to execute.
*/
void instr_execute_lparam(UScriptRuntimeContext *ctx, UScriptInstruction *instr) {
	//TODO: error handling
	FunctionArgument **args = ctx->cur_frame->func_ctx->args;
	int32_t idx = *(int32_t*)instr->operand;

	StackEntry *entry;
	stack_entry_create(&entry, args[idx]->obj.desc.type);

	memcpy(entry->obj->data, args[idx]->obj.data,
		uscript_type_size(entry->obj->desc.type));

	eval_stack_push(ctx->cur_frame->func_ctx->eval_stack, entry);
}

//! Executes a ADD instruction from the current IP.
/*!
	\param[in] ctx The current runtime context.
	\param[in] instr The instruction to execute.
*/
void instr_execute_add(UScriptRuntimeContext *ctx, UScriptInstruction *instr) {
	//TODO: error handling
	RuntimeObject *val1 = eval_stack_pop(ctx->cur_frame->func_ctx->eval_stack)->obj;
	RuntimeObject *val2 = eval_stack_pop(ctx->cur_frame->func_ctx->eval_stack)->obj;

	if(runtime_obj_add(val1, val2) != USCRIPT_ERR_SUCCESS) {
		//TODO: ERROR HANDLING
	}

	runtime_obj_destroy(val2);

	StackEntry *entry;
	stack_entry_create(&entry, val1->desc.type);
	entry->obj = val1;

	eval_stack_push(ctx->cur_frame->func_ctx->eval_stack, entry);
}