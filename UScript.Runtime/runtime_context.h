#ifndef RUNTIME_CONTEXT_H
#define RUNTIME_CONTEXT_H
#include <stdint.h>

struct RuntimeDescriptor {
	uint32_t ip;
};

struct RuntimeContext {
	struct RuntimeDescriptor desc;

};

#endif
