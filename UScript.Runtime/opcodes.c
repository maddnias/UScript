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
void execute_instr_li32(UScriptRuntimeContext *ctx, UScriptInstruction *instr) {
	StackEntry *entry;
	stack_entry_create(&entry, I32);

	*(int32_t*)entry->type_desc->data = *(int32_t*)instr->operand;

	// TODO: error handling
	if (eval_stack_push(ctx->cur_desc->func_ctx->eval_stack, entry) != USCRIPT_ERR_SUCCESS) {
		return;
	}
}

//! Executes a SCALL instruction from the current IP.
/*!
	\param[in] ctx The current runtime context.
	\param[in] instr The instruction to execute.
*/
void execute_instr_scall(UScriptRuntimeContext *ctx, UScriptInstruction *instr) {
	FunctionMetadataRow *funcRow;

	if (resolve_func_token(&funcRow, ctx->md_ctx,
		*(int32_t*)instr->operand) != USCRIPT_ERR_SUCCESS) {
		//TODO: error handling
		return;
	}

	if(create_push_stack_frame(ctx) != USCRIPT_ERR_SUCCESS) {
		//TODO: error handling
		return;
	}

	StackFrame *previousFrame = stack_frame_get_previous(ctx);

	populate_function_args(ctx->cur_desc->func_ctx, previousFrame->func_ctx->eval_stack,
		funcRow);

	ctx->cur_desc->ip = funcRow->code_relative_addr;
}

//! Executes a LPARAM instruction from the current IP.
/*!
	\param[in] ctx The current runtime context.
	\param[in] instr The instruction to execute.
*/
void execute_instr_lparam(UScriptRuntimeContext *ctx, UScriptInstruction *instr) {
	//TODO: error handling
	FunctionArgument **args = ctx->cur_desc->func_ctx->args;
	int32_t idx = *(int32_t*)instr->operand;

	StackEntry *entry;
	stack_entry_create(&entry, args[idx]->type_desc.type);

	memcpy(entry->type_desc->data, args[idx]->type_desc.data, uscript_type_size(entry->type_desc->type));

	eval_stack_push(ctx->cur_desc->func_ctx->eval_stack, entry);
}