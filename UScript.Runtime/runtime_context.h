#ifndef RUNTIME_CONTEXT_H
#define RUNTIME_CONTEXT_H
#include <stdint.h>
#include "metadata_context.h"
#include "function_context.h"

typedef struct RuntimeDescriptor {
	uint32_t ip;
	FunctionContext *func_ctx;
} RuntimeDescriptor;

typedef struct UScriptRuntimeContext {
	UScriptMetadataContext* md_ctx;
	RuntimeDescriptor* desc;

} UScriptRuntimeContext;

#endif
