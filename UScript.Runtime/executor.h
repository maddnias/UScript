#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "include/metadata_context.h"
#include "runtime_context.h"
#include "include/error.h"
#include "eval_stack.h"
#include "opcodes.h"

typedef struct UScriptInstruction {
	UScriptOpCode code;


} UScriptInstruction;

//! Executes the next instruction from the current position in the codeblock.
USCRIPT_ERR execute_next(UScriptRuntimeContext *ctx);

//! Creates a runtime context.
USCRIPT_ERR create_runtime_ctx(UScriptRuntimeContext **ctx, UScriptMetadataContext *mdCtx);

//! Parses the next instruction from the current position in the codeblock.
USCRIPT_ERR parse_next_instr(UScriptRuntimeContext *ctx, UScriptInstruction **instr);

//! Reads a char from the current position in the codeblock.
char read_next_char(UScriptRuntimeContext *ctx);

//! Reads a 32-bit integer from the current position in the codeblock.
int32_t read_next_i32(UScriptRuntimeContext *ctx);

//! Executes a LI32 instruction from the current IP.
void execute_instr_li32(UScriptRuntimeContext *ctx);

#endif
