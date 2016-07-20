#include "data_types.h"
#include <stdlib.h>

//! Creates a type descriptor.
/*!
	\param[out] desc The type descriptor.
	\param[in] type The type of the descriptor.
*/
void type_desc_create(UScriptTypeDesc **desc, uscript_datatype type) {
	*desc = (UScriptTypeDesc*)malloc(sizeof(UScriptTypeDesc));
	(*desc)->type = type;
	(*desc)->is_array = false;
	(*desc)->data = NULL;
	int32_t typeSize = uscript_type_size(type);

	//TODO: error handling
	if (typeSize != -1) {
		(*desc)->data = (char*)malloc(uscript_type_size(type));
	}
}

//! Destroys a type descriptor.
/*!
	\param[in] desc The type descriptor.
*/
void type_desc_destroy(UScriptTypeDesc *desc) {
	if (desc->data != NULL) {
		free(desc->data);
	}
	free(desc);
}

//! Determines the size of the inputted uscript_datatype.
/*!
	\param[in] type The type to calculate size of.

	\return The size of the uscript_datatype in memory.
*/
int32_t uscript_type_size(uscript_datatype type) {
	switch(type) {
	case BYTE:
	case CHAR:
	case BOOL:
		return 1;
	case I16:
	case U16:
		return 2;
	case I32:
	case U32: 
		return 4;
	case I64: 
	case U64:
		return 8;
	default: 
		return -1;
	}
}
