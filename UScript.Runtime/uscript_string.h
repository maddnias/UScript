#ifndef USCRIPT_STRING_H
#define USCRIPT_STRING_H
#include <stdint.h>
#include <stdbool.h>

typedef struct UScriptString {
	int32_t len;
	char *data;
	bool initialized;
} UScriptString;

UScriptString* uscript_string_alloc(int32_t);

UScriptString* uscript_string_create(int32_t, char *);

void uscript_string_set_data(UScriptString **str, char *data);

void uscript_string_destroy(UScriptString *str);

bool uscript_string_is_equal(UScriptString *str1, UScriptString *str2);

UScriptString* uscript_string_append(UScriptString *str1, UScriptString *str2);

bool __ensure_uscript_string_initialized(int n_str, ...);

#endif