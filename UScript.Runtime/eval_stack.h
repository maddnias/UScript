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
/*!
	\param[out] entry The stack entry.
	\param[in] type The type of the stack entry
*/
void stack_entry_create(StackEntry **entry, uscript_datatype type);

//! Destroys a stack entry
/*!
	\param[in] entry The stack entry to destroy.
*/
void stack_entry_destroy(StackEntry *entry);

//! Creates a new evaluation stack.
/*!
	\param[out] stack The evaluation stack.
*/
void eval_stack_create(EvalStack **stack);

//! Destroys an evaluation stack.
/*!
	\param[in] stack The evaluation stack.
*/
void eval_stack_destroy(EvalStack *stack);

//! Pushes a stack entry to an evaluation stack.
/*!
	\param[in] stack The evaluation stack.
	\param[in] entry The stack entry.
*/
USCRIPT_ERR eval_stack_push(EvalStack *stack, StackEntry *entry);

//! Pops a stack entry from an evaluation stack.
/*!
	\param[in] stack The evaluation stack.

	\return The entry that was popped from the evaluation stack.
*/
StackEntry* eval_stack_pop(EvalStack *stack);

#endif