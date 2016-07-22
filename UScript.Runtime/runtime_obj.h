#ifndef RUNTIME_OBJ_H
#define RUNTIME_OBJ_H
#include "data_types.h"
#include "include/error.h"

typedef struct RuntimeObject {
	UScriptTypeDesc desc;
	char* data;
} RuntimeObject;

//! Creates a runtime object.
void runtime_obj_create(RuntimeObject **obj, uscript_datatype type);

//! Destroys a runtime object.
void runtime_obj_destroy(RuntimeObject *obj);

//! Adds two runtime objects together
USCRIPT_ERR runtime_obj_add(RuntimeObject *obj1, RuntimeObject *obj2);

USCRIPT_ERR runtime_obj_sub(RuntimeObject *obj1, RuntimeObject *obj2);

USCRIPT_ERR runtime_obj_mul(RuntimeObject *obj1, RuntimeObject *obj2);

USCRIPT_ERR runtime_obj_div(RuntimeObject *obj1, RuntimeObject *obj2);

USCRIPT_ERR runtime_obj_xor(RuntimeObject *obj1, RuntimeObject *obj2);
#endif
