#ifndef DATA_TYPES_H
#define DATA_TYPES_H
#include <stdbool.h>
#include <stdint.h>

typedef enum {
	RUNTIME_DETERMINED,
	BYTE,
	CHAR,
	BOOL,
	I16,
	I32,
	I64,
	U16,
	U32,
	U64,
	VOID
} uscript_datatype;

typedef struct UScriptTypeDescriptor {
	uscript_datatype type;
	bool is_array;
	char* data;
} UScriptTypeDesc;

//! Creates a type descriptor.
void type_desc_create(UScriptTypeDesc **desc, uscript_datatype type);

//! Destroys a type descriptor.
void type_desc_destroy(UScriptTypeDesc *desc);

//! Determines the size of the inputted uscript_datatype.
int32_t uscript_type_size(uscript_datatype type);

#endif