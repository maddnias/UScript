#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "runtime_context.h"
#include "include/error.h"
#include "instruction.h"

//! Executes the next instruction from the current position in the codeblock.
USCRIPT_ERR execute_next(UScriptRuntimeContext *ctx);

//! Parses the next instruction from the current position in the codeblock.
USCRIPT_ERR parse_next_instr(UScriptRuntimeContext *ctx, UScriptInstruction **instr);

//! Reads a char from the current position in the codeblock.
char read_next_char(UScriptRuntimeContext *ctx);

//! Reads a 32-bit integer from the current position in the codeblock.
int32_t read_next_i32(UScriptRuntimeContext *ctx);

#endif
