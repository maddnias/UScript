#ifndef DATA_TYPES_H
#define DATA_TYPES_H
#include <stdbool.h>

typedef enum {
	BYTE,
	CHAR,
	BOOL,
	I16,
	I32,
	I64,
	U16,
	U32,
	U64
} uscript_datatype;

typedef struct UScriptTypeDescriptor {
	uscript_datatype type;
	bool is_array;
} UScriptTypeDesc;

#endif