#include "runtime_obj.h"
#include <stdlib.h>
#include <stdarg.h>

//! Creates a runtime object.
/*!
	\param[out] obj The runtime object.
	\param[in] type The type of the descriptor.
*/
void runtime_obj_create(RuntimeObject** obj, uscript_datatype type) {
	*obj = (RuntimeObject*)malloc(sizeof(RuntimeObject));
	UScriptTypeDesc *desc;
	type_desc_create(&desc, type);

	(*obj)->desc = *desc;
	type_desc_destroy(desc);

	int32_t typeSize = uscript_type_size(type);

	//TODO: error handling
	if (typeSize != -1) {
		(*obj)->data = (char*)malloc(uscript_type_size(type));
	}
}

//! Destroys a runtime object.
/*!
	\param[in] obj The runtime object to destroy.
*/
void runtime_obj_destroy(RuntimeObject *obj) {
	if (obj->data != NULL) {
		free(obj->data);
	}

	free(obj);
}

bool __ensure_not_runtime_determined(int n_obj, ...) {
	va_list ap;
	va_start(ap, n_obj);

	for (int i = 0; i < n_obj; i++) {
		RuntimeObject *curObj = va_arg(ap, RuntimeObject*);
		if (curObj->desc.type == RUNTIME_DETERMINED
			|| curObj->desc.type == VOID)
			return false;
	}

	va_end(ap);
	return true;
}

//! Adds two runtime objects together
/*!
	\param[in] obj1 The first runtime object.
	\param[in] obj2 The second runtime object.
	\remark obj1 is the resulting object after the operation.
*/
USCRIPT_ERR runtime_obj_add(RuntimeObject* obj1, RuntimeObject* obj2) {
	if(!__ensure_not_runtime_determined(2, obj1, obj2)) {
		return USCRIPT_ERR_UNK;
	}
	
	switch(obj1->desc.type) {

	case BYTE: break;
	case CHAR: break;
	case BOOL: break;
	case I16: break;
	case I32: 
		switch (obj2->desc.type) {

		case BYTE: break;
		case CHAR: break;
		case BOOL: break;
		case I16: break;
		case I32: 
			*(int32_t*)obj1->data += *(int32_t*)obj2->data;
			break;
		case I64: break;
		case U16: break;
		case U32: break;
		case U64: break;
		case VOID: break;
		default: break;
		}
		break;
	case I64: break;
	case U16: break;
	case U32: break;
	case U64: break;
	case VOID: break;
	default: break;
	}

	return USCRIPT_ERR_SUCCESS;
}

USCRIPT_ERR runtime_obj_sub(RuntimeObject* obj1, RuntimeObject* obj2) {
	if (!__ensure_not_runtime_determined(2, obj1, obj2)) {
		return USCRIPT_ERR_UNK;
	}

	switch (obj1->desc.type) {

	case BYTE: break;
	case CHAR: break;
	case BOOL: break;
	case I16: break;
	case I32:
		switch (obj2->desc.type) {

		case BYTE: break;
		case CHAR: break;
		case BOOL: break;
		case I16: break;
		case I32:
			*(int32_t*)obj1->data -= *(int32_t*)obj2->data;
			break;
		case I64: break;
		case U16: break;
		case U32: break;
		case U64: break;
		case VOID: break;
		default: break;
		}
		break;
	case I64: break;
	case U16: break;
	case U32: break;
	case U64: break;
	case VOID: break;
	default: break;
	}

	return USCRIPT_ERR_SUCCESS;
}

USCRIPT_ERR runtime_obj_mul(RuntimeObject* obj1, RuntimeObject* obj2) {
	if (!__ensure_not_runtime_determined(2, obj1, obj2)) {
		return USCRIPT_ERR_UNK;
	}

	switch (obj1->desc.type) {

	case BYTE: break;
	case CHAR: break;
	case BOOL: break;
	case I16: break;
	case I32:
		switch (obj2->desc.type) {

		case BYTE: break;
		case CHAR: break;
		case BOOL: break;
		case I16: break;
		case I32:
			*(int32_t*)obj1->data *= *(int32_t*)obj2->data;
			break;
		case I64: break;
		case U16: break;
		case U32: break;
		case U64: break;
		case VOID: break;
		default: break;
		}
		break;
	case I64: break;
	case U16: break;
	case U32: break;
	case U64: break;
	case VOID: break;
	default: break;
	}


	return USCRIPT_ERR_SUCCESS;
}

USCRIPT_ERR runtime_obj_change_type(RuntimeObject* obj, uscript_datatype type) {
	//TODO: error handling

	return USCRIPT_ERR_UNK;
}
