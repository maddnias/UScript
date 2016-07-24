#include "executor.h"
#include "opcodes.h"
#include <stdlib.h>
#include <memory.h>
#include "metadata.h"

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
	case ADD: 
		instr_execute_add(ctx, instr);
		break;
	case SUB: break;
	case DIV: break;
	case MUL: break;
	case SCALL: 
		instr_execute_scall(ctx, instr);
		break;
	case LSTR: break;
	case RET: 
		instr_execute_ret(ctx, instr);
		break;
	case LPARAM: 
		instr_execute_lparam(ctx, instr);
		break;
	case LI32: 
		instr_execute_li32(ctx, instr);
		break;
	default: break;
	}

	free(instr);
	return USCRIPT_ERR_SUCCESS;
}

//! Parses the next instruction from the current position in the codeblock.
/*!
	\param[in] ctx The current runtime context.
	\param[out] instr The instruction.
*/
USCRIPT_ERR parse_next_instr(UScriptRuntimeContext *ctx, UScriptInstruction **instr) {
	// we're in entry code
	if(ctx->frame_count == 1
		&& ctx->cur_frame->ip >= ctx->md_ctx->entry_code_block_size) {
		// End of code reached
		return USCRIPT_ERR_UNK;
	}
	
	char rawOp = read_next_char(ctx);
	
	if(rawOp < 0 || rawOp > USCRIPT_OP_MAX) {
		return USCRIPT_ERR_UNKNOWN_OP;
	}

	*instr = (UScriptInstruction*)malloc(sizeof(UScriptInstruction));
	(*instr)->code = (UScriptOpCode)rawOp;
	
	switch((*instr)->code) {

	case SVAR: break;
	case LVAR: break;
	case SLVAR: break;
	case ADD: 
		(*instr)->has_operand = false;
		(*instr)->stack_impact = POP1;
		break;
	case SUB: break;
	case DIV: break;
	case MUL: break;
	case SCALL: 
		(*instr)->has_operand = true;
		(*instr)->operand_type = OPERAND_TOKEN;
		(*instr)->operand = (char*)malloc(sizeof(int32_t));
		*(int32_t*)(*instr)->operand = read_next_i32(ctx);
		(*instr)->stack_impact = FUNCTION_CALL;
		break;
	case LSTR: break;
	case RET: 
		(*instr)->has_operand = false;
		(*instr)->stack_impact = RETURN_STMT;
		break;
	case LPARAM: 
		(*instr)->has_operand = true;
		(*instr)->operand_type = OPERAND_DIRECT_I32;
		(*instr)->stack_impact = PUSH1;
		(*instr)->operand = (char*)malloc(sizeof(int32_t));
		*(int32_t*)(*instr)->operand = read_next_i32(ctx);
		break;
	case LI32: 
		(*instr)->has_operand = true;
		(*instr)->operand_type = OPERAND_DIRECT_I32;
		(*instr)->stack_impact = PUSH1;
		(*instr)->operand = (char*)malloc(sizeof(int32_t));
		*(int32_t*)(*instr)->operand = read_next_i32(ctx);
		break;
	default: break;
	}

	return USCRIPT_ERR_SUCCESS;
}


//! Reads a char from the current position in the codeblock.
/*!
	\param[in] ctx The current runtime context.
	\return The read char.
*/
char read_next_char(UScriptRuntimeContext *ctx) {
	return *(ctx->md_ctx->code_block + ctx->cur_frame->ip++);
}


//! Reads a 32-bit integer from the current position in the codeblock.
/*!
	\param[in] ctx The current runtime context.
	\return The read int32_t.
*/
int32_t read_next_i32(UScriptRuntimeContext *ctx) {
	int32_t val = *(int32_t*)(ctx->md_ctx->code_block + ctx->cur_frame->ip);
	ctx->cur_frame->ip += sizeof(int32_t);

	return val;
}
