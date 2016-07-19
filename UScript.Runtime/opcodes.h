#ifndef OPCODES_H
#define OPCODES_H

#define USCRIPT_OP_MAX 11

typedef enum UScriptOpCode
{
	SVAR,
	LVAR,
	SLVAR,
	ADD,
	SUB,
	DIV,
	MUL,
	SCALL,
	LSTR,
	RET,
	LPARAM,
	LI32
} UScriptOpCode;

#endif
