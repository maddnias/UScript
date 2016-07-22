#ifndef OPCODES_H
#define OPCODES_H
#define USCRIPT_OP_MAX 11
#include "executor.h"

//! Executes a LI32 instruction from the current IP.
void instr_execute_li32(UScriptRuntimeContext *ctx, UScriptInstruction *instr);

//! Executes a SCALL instruction from the current IP.
void instr_execute_scall(UScriptRuntimeContext *ctx, UScriptInstruction *instr);

//! Executes a LPARAM instruction from the current IP.
void instr_execute_lparam(UScriptRuntimeContext *ctx, UScriptInstruction *instr);

//! Executes a ADD instruction from the current IP.
void instr_execute_add(UScriptRuntimeContext *ctx, UScriptInstruction *instr);
#endif
