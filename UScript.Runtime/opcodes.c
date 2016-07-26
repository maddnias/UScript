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

	ctx->call_stack[ctx->frame_count - 1]->func_ctx->return_type_desc = *funcRow->return_type;

	StackFrame *previousFrame;
	call_stack_get_previous_frame(ctx, &previousFrame);

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

//! Executes an ADD instruction from the current IP.
/*!
	\param[in] ctx The current runtime context.
	\param[in] instr The instruction to execute.
*/
void instr_execute_add(UScriptRuntimeContext *ctx, UScriptInstruction *instr) {
	//TODO: error handling
	StackEntry *entry1, *entry2;

	if(eval_stack_pop(ctx->cur_frame->func_ctx->eval_stack, &entry1) != USCRIPT_ERR_SUCCESS) {
		//TODO: error handling
	}

	if (eval_stack_pop(ctx->cur_frame->func_ctx->eval_stack, &entry2) != USCRIPT_ERR_SUCCESS) {
		//TODO: error handling
	}

	if(runtime_obj_add(entry1->obj, entry2->obj) != USCRIPT_ERR_SUCCESS) {
		//TODO: ERROR HANDLING
	}

	StackEntry *entry;
	stack_entry_create(&entry, entry1->obj->desc.type);
	entry->obj = entry1->obj;

	stack_entry_destroy(entry2);
	eval_stack_push(ctx->cur_frame->func_ctx->eval_stack, entry);
}

void instr_execute_sub(UScriptRuntimeContext* ctx, UScriptInstruction* instr) {
	//TODO: error handling
	StackEntry *entry1, *entry2;

	if (eval_stack_pop(ctx->cur_frame->func_ctx->eval_stack, &entry1) != USCRIPT_ERR_SUCCESS) {
		//TODO: error handling
	}

	if (eval_stack_pop(ctx->cur_frame->func_ctx->eval_stack, &entry2) != USCRIPT_ERR_SUCCESS) {
		//TODO: error handling
	}

	if (runtime_obj_sub(entry1->obj, entry2->obj) != USCRIPT_ERR_SUCCESS) {
		//TODO: ERROR HANDLING
	}

	StackEntry *entry;
	stack_entry_create(&entry, entry1->obj->desc.type);
	entry->obj = entry1->obj;

	stack_entry_destroy(entry2);
	eval_stack_push(ctx->cur_frame->func_ctx->eval_stack, entry);
}

//! Executes a RET instruction from the current IP.
/*!
	\param[in] ctx The current runtime context.
	\param[in] instr The instruction to execute.
*/
void instr_execute_ret(UScriptRuntimeContext *ctx, UScriptInstruction *instr) {
	//TODO: error handling
	UScriptTypeDesc retTypeDesc;
	StackFrame *lastFrame, *targetFrame;
	StackEntry *retval = NULL;

	call_stack_get_previous_frame(ctx, &targetFrame);
	call_stack_unwind_one(ctx, &lastFrame);

	retTypeDesc = lastFrame->func_ctx->return_type_desc;
	if (retTypeDesc.type != VOID) {
		if (eval_stack_pop(lastFrame->func_ctx->eval_stack, &retval) != USCRIPT_ERR_SUCCESS) {
			//TODO: error handling
		}

		if(retTypeDesc.type != retval->obj->desc.type) {
			if(retTypeDesc.type == RUNTIME_DETERMINED) {
				retTypeDesc.type = retval->obj->desc.type;
			}
		}

		if(eval_stack_push(targetFrame->func_ctx->eval_stack, retval) != USCRIPT_ERR_SUCCESS) {
			//TODO: error handling
		}
	}

}

void instr_execute_mul(UScriptRuntimeContext* ctx, UScriptInstruction* instr) {
	//TODO: error handling
	StackEntry *entry1, *entry2;

	if (eval_stack_pop(ctx->cur_frame->func_ctx->eval_stack, &entry1) != USCRIPT_ERR_SUCCESS) {
		//TODO: error handling
	}

	if (eval_stack_pop(ctx->cur_frame->func_ctx->eval_stack, &entry2) != USCRIPT_ERR_SUCCESS) {
		//TODO: error handling
	}

	if (runtime_obj_mul(entry1->obj, entry2->obj) != USCRIPT_ERR_SUCCESS) {
		//TODO: ERROR HANDLING
	}

	StackEntry *entry;
	stack_entry_create(&entry, entry1->obj->desc.type);
	entry->obj = entry1->obj;

	stack_entry_destroy(entry2);
	eval_stack_push(ctx->cur_frame->func_ctx->eval_stack, entry);
}
