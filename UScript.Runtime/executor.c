#include "executor.h"
#include "opcodes.h"
#include <stdlib.h>

//! Executes the next instruction from the current position in the codeblock.
/*!
	\param[in] ctx The runtime context.
*/
USCRIPT_ERR execute_next(UScriptRuntimeContext *ctx) {
	UScriptInstruction *instr;
	USCRIPT_ERR res;

	if((res = parse_next_instr(ctx, &instr)) != USCRIPT_ERR_SUCCESS) {
		return res;
	}

	switch (instr->code) {
	case SVAR: break;
	case LVAR: break;
	case SLVAR: break;
	case ADD: break;
	case SUB: break;
	case DIV: break;
	case MUL: break;
	case SCALL: break;
	case LSTR: break;
	case RET: break;
	case LPARAM: break;
	case LI32: 
		execute_instr_li32(ctx);
		break;
	default: break;
	}

	free(instr);

	return USCRIPT_ERR_SUCCESS;
}

//! Creates a runtime context.
/*!
	\param[out] ctx The runtime context.
	\param[in] mdCtx The metadata context to use.
*/
USCRIPT_ERR create_runtime_ctx(UScriptRuntimeContext **ctx, UScriptMetadataContext *mdCtx) {
	*ctx = (UScriptRuntimeContext*)malloc(sizeof(UScriptRuntimeContext));
	(*ctx)->md_ctx = mdCtx;

	RuntimeDescriptor *desc = (RuntimeDescriptor*)malloc(sizeof(RuntimeDescriptor));
	(*ctx)->desc = desc;
	(*ctx)->desc->ip = 0;
	__create_basic_function_ctx(&(*ctx)->desc->func_ctx);

	return USCRIPT_ERR_SUCCESS;
}


//! Parses the next instruction from the current position in the codeblock.
/*!
	\param[in] ctx The current runtime context.
	\param[out] instr The instruction.
*/
USCRIPT_ERR parse_next_instr(UScriptRuntimeContext *ctx, UScriptInstruction **instr) {
	char rawOp = read_next_char(ctx);
	
	if(rawOp < 0 || rawOp > USCRIPT_OP_MAX) {
		return USCRIPT_ERR_UNKNOWN_OP;
	}

	*instr = (UScriptInstruction*)malloc(sizeof(UScriptInstruction));
	(*instr)->code = (UScriptOpCode)rawOp;
	
	return USCRIPT_ERR_SUCCESS;
}


//! Reads a char from the current position in the codeblock.
/*!
	\param[in] ctx The current runtime context.

	\return The read char.
*/
char read_next_char(UScriptRuntimeContext *ctx) {
	return *(ctx->md_ctx->code_block + ctx->desc->ip++);
}


//! Reads a 32-bit integer from the current position in the codeblock.
/*!
	\param[in] ctx The current runtime context.

	\return The read int32_t.
*/
int32_t read_next_i32(UScriptRuntimeContext *ctx) {
	int32_t val = *(int32_t*)(ctx->md_ctx->code_block + ctx->desc->ip);
	ctx->desc->ip += sizeof(int32_t);

	return val;
}

//! Executes a LI32 instruction from the current IP.
/*!
	\param[in] ctx The current runtime context.
*/
void execute_instr_li32(UScriptRuntimeContext *ctx) {
	int32_t operand = read_next_i32(ctx);

	StackEntry *entry;
	stack_entry_create(&entry, I32);

	*(int32_t*)entry->type_desc->data = operand;
	
	// TODO: error handling
	if(eval_stack_push(ctx->desc->func_ctx->eval_stack, entry) != USCRIPT_ERR_SUCCESS) {
		return;
	}
}