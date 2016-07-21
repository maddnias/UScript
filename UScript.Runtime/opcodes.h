#ifndef OPCODES_H
#define OPCODES_H
#define USCRIPT_OP_MAX 11
#include "executor.h"

//! Executes a LI32 instruction from the current IP.
void execute_instr_li32(UScriptRuntimeContext *ctx, UScriptInstruction *instr);

//! Executes a SCALL instruction from the current IP.
void execute_instr_scall(UScriptRuntimeContext *ctx, UScriptInstruction *instr);

//! Executes a LPARAM instruction from the current IP.
void execute_instr_lparam(UScriptRuntimeContext *ctx, UScriptInstruction *instr);
#endif
