#ifndef INSTRUCTION_H
#define INSTRUCTION_H

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

typedef enum operand_type_t {
	OPERAND_TOKEN,
	OPERAND_DIRECT_I32,
	OPERAND_DIRECT_BYTE,
} operand_type_t;

typedef enum stack_impact_t {
	NONE,
	PUSH1,
	PUSH2,
	POP1,
	POP2,
	FUNCTION_CALL
} stack_impact_t;

typedef struct UScriptInstruction {
	UScriptOpCode code;
	stack_impact_t stack_impact;
	bool has_operand;
	operand_type_t operand_type;
	char* operand;
} UScriptInstruction;

#endif
