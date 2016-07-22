#include "runtime_obj.h"
#include <stdlib.h>

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