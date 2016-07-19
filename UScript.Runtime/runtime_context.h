#ifndef RUNTIME_CONTEXT_H
#define RUNTIME_CONTEXT_H
#include <stdint.h>

typedef struct RuntimeDescriptor {
	uint32_t ip;
} RuntimeDescriptor;

typedef struct RuntimeContext {
	RuntimeDescriptor desc;

} RuntimeContext;

#endif
