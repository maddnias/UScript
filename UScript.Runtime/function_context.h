#ifndef FUNCTION_CONTEXT_H
#define FUNCTION_CONTEXT_H

#include "data_types.h"
#include <stdint.h>

typedef struct FunctionArgument {
	UScriptTypeDesc type_desc;
	int32_t idx;
} FunctionArgument;

#endif