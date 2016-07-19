#ifndef DATA_TYPES_H
#define DATA_TYPES_H
#include <stdbool.h>
#include <stdint.h>

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
	char* data;
} UScriptTypeDesc;

void type_desc_create(UScriptTypeDesc **desc, uscript_datatype type);
void type_desc_destroy(UScriptTypeDesc *desc);

int32_t uscript_type_size(uscript_datatype type);

#endif