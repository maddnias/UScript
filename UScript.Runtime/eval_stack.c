#include "eval_stack.h"
#include <stdlib.h>
#include <memory.h>

//! Creates a new stack entry.
/*!
	\param[out] entry The stack entry.
	\param[in] type The type of the stack entry
*/
void stack_entry_create(StackEntry **entry, uscript_datatype type) {
	*entry = (StackEntry*)malloc(sizeof(StackEntry));
	type_desc_create(&(*entry)->type_desc, type);
}

//! Destroys a stack entry
/*!
	\param[in] entry The stack entry to destroy.
*/
void stack_entry_destroy(StackEntry *entry) {
	type_desc_destroy(entry->type_desc);
	free(entry);
}

//! Creates a new evaluation stack.
/*!
	\param[out] stack The evaluation stack.
*/
void eval_stack_create(EvalStack **stack) {
	*stack = (EvalStack*)malloc(sizeof(EvalStack));

	(*stack)->current_size = 0;
	(*stack)->max_size = 8;
	(*stack)->entries = (StackEntry**)malloc((*stack)->max_size * sizeof(StackEntry*));
}

//! Destroys an evaluation stack.
/*!
	\param[in] stack The evaluation stack.
*/
void eval_stack_destroy(EvalStack *stack) {
	for(int i = stack->current_size;i > 0;i--) {
		stack_entry_destroy(stack->entries[i-1]);
	}
	free(stack);
}

//! Pushes a stack entry to an evaluation stack.
/*!
	\param[in] stack The evaluation stack.
	\param[in] entry The stack entry.
*/
USCRIPT_ERR eval_stack_push(EvalStack *stack, StackEntry *entry) {
	if(stack->current_size +1 > stack->max_size) {
		return USCRIPT_ERR_STACK_OVERFLOW;
	}

	stack->entries[stack->current_size] = entry;
	stack->current_size++;

	return USCRIPT_ERR_SUCCESS;
}

// TODO: under/over flow checks
//! Pops a stack entry from an evaluation stack.
/*!
	\param[in] stack The evaluation stack.

	\return The entry that was popped from the evaluation stack.

	\remark
		The original stack entry on top of the stack is destroyed in the process.
*/
StackEntry* eval_stack_pop(EvalStack *stack) {
	StackEntry *popped = stack->entries[stack->current_size - 1];
	StackEntry *entry;
	
	stack_entry_create(&entry, popped->type_desc->type);
	entry->type_desc->is_array = popped->type_desc->is_array;

	memcpy(entry->type_desc->data, popped->type_desc->data,
		uscript_type_size(popped->type_desc->type));

	stack_entry_destroy(stack->entries[stack->current_size-- -1]);
	return entry;
}