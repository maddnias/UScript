#ifndef USCRIPT_STRING_H
#define USCRIPT_STRING_H
#include <stdint.h>
#include <stdbool.h>

typedef struct UScriptString {
	int32_t len;
	char *data;
	bool initialized;
} UScriptString;

UScriptString* alloc_uscript_string(int32_t);

UScriptString* create_uscript_string(int32_t, char *);

void set_uscript_string_data(UScriptString **str, char *data);

void destroy_uscript_string(UScriptString *str);

bool uscript_string_is_equal(UScriptString *str1, UScriptString *str2);

#endif