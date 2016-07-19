#include "executor.h"
#include "opcodes.h"
#include <stdlib.h>

USCRIPT_ERR execute_next(UScriptRuntimeContext *ctx) {
	UScriptInstruction *instr;
	USCRIPT_ERR res;

	if((res = parse_next_instr(ctx, &instr)) != USCRIPT_ERR_SUCCESS) {
		return res;
	}

	//exec instr
	free(instr);

	return USCRIPT_ERR_SUCCESS;
}

USCRIPT_ERR create_runtime_ctx(UScriptRuntimeContext **ctx, UScriptMetadataContext *mdCtx) {
	*ctx = (UScriptRuntimeContext*)malloc(sizeof(UScriptRuntimeContext));
	(*ctx)->md_ctx = mdCtx;

	RuntimeDescriptor *desc = (RuntimeDescriptor*)malloc(sizeof(RuntimeDescriptor));
	(*ctx)->desc = desc;

	(*ctx)->desc->ip = 0;

	return USCRIPT_ERR_SUCCESS;
}

USCRIPT_ERR parse_next_instr(UScriptRuntimeContext *ctx, UScriptInstruction **instr) {

	char rawOp = *(ctx->md_ctx->code_block + ctx->desc->ip);
	
	if(rawOp < 0 || rawOp > USCRIPT_OP_MAX) {
		return USCRIPT_ERR_UNKNOWN_OP;
	}

	*instr = (UScriptInstruction*)malloc(sizeof(UScriptInstruction));
	(*instr)->code = (UScriptOpCode)rawOp;
	
	return USCRIPT_ERR_SUCCESS;
}