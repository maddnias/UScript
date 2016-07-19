#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "include/metadata_context.h"
#include "runtime_context.h"
#include "include/error.h"
#include "opcodes.h"

typedef struct UScriptInstruction {
	UScriptOpCode code;


} UScriptInstruction;

USCRIPT_ERR execute_next(UScriptRuntimeContext *ctx);

USCRIPT_ERR create_runtime_ctx(UScriptRuntimeContext **ctx, UScriptMetadataContext *mdCtx);

USCRIPT_ERR parse_next_instr(UScriptRuntimeContext *ctx, UScriptInstruction **instr);
#endif
