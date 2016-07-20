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

//! Creates a new stack entry.
void stack_entry_create(StackEntry **entry, uscript_datatype type);

//! Destroys a stack entry
void stack_entry_destroy(StackEntry *entry);

//! Creates a new evaluation stack.
void eval_stack_create(EvalStack **stack);

//! Destroys an evaluation stack.
void eval_stack_destroy(EvalStack *stack);

//! Pushes a stack entry to an evaluation stack.
USCRIPT_ERR eval_stack_push(EvalStack *stack, StackEntry *entry);

//! Pops a stack entry from an evaluation stack.
StackEntry* eval_stack_pop(EvalStack *stack);

#endif