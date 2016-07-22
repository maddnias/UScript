#ifndef RUNTIME_OBJ_H
#define RUNTIME_OBJ_H
#include "data_types.h"

typedef struct RuntimeObject {
	UScriptTypeDesc desc;
	char* data;
} RuntimeObject;

//! Creates a runtime object.
void runtime_obj_create(RuntimeObject **obj, uscript_datatype type);

//! Destroys a runtime object.
void runtime_obj_destroy(RuntimeObject *obj);

#endif
