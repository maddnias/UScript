#ifndef EVAL_STACK_H
#define EVAL_STACK_H

#include <stdint.h>
#include "data_types.h"
#include "include/error.h"

typedef struct StackEntry {
	UScriptTypeDesc* type_desc;
} StackEntry;

typedef struct EvalStack {
	int32_t max_size;
	int32_t current_size;
	StackEntry **entries;
} EvalStack;

void stack_entry_create(StackEntry **entry, uscript_datatype type);
void stack_entry_destroy(StackEntry *entry);

void eval_stack_create(EvalStack **stack);
void eval_stack_destroy(EvalStack *stack);
StackEntry* eval_stack_pop(EvalStack *stack);
USCRIPT_ERR eval_stack_push(EvalStack *stack, StackEntry *entry);

#endif