#ifndef USCRIPT_STRING_H
#define USCRIPT_STRING_H
#include <stdint.h>
#include <stdbool.h>

struct UScriptString {
	int32_t len;
	char *data;
	bool initialized;
};

struct UScriptString* alloc_uscript_string(int32_t);

struct UScriptString* create_uscript_string(int32_t, char *);

void set_uscript_string_data(struct UScriptString **str, char *data);

void destroy_uscript_string(struct UScriptString *str);

#endif