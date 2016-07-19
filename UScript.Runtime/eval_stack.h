#ifndef EVAL_STACK_H
#define EVAL_STACK_H
#include <stdint.h>
#include "data_types.h"

typedef struct StackEntry {
	uscript_datatype type;
	char* data;
} StackEntry;

typedef struct EvalStack {
	int32_t max_size;
	int32_t current_size;
} EvalStack;

#endif