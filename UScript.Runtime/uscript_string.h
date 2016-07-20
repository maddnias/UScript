//! \file uscript_string.h

#ifndef USCRIPT_STRING_H
#define USCRIPT_STRING_H
#include <stdint.h>
#include <stdbool.h>

typedef struct UScriptString {
	int32_t len;
	char *data;
	bool initialized;
} UScriptString;

//! Allocates memory for a new uscript_string.
UScriptString* uscript_string_alloc(int32_t);

//! Creates a uscript_string and sets the data.
UScriptString* uscript_string_create(int32_t, char *);

//! Set the string data in an uscript_string.
void uscript_string_set_data(UScriptString *str, char *data);

//! Destroys an uscript_string.
void uscript_string_destroy(UScriptString *str);

//! Checks if two uscript_strings are equal to each other.
bool uscript_string_is_equal(UScriptString *str1, UScriptString *str2);

//! Appends two uscript_strings into one.
UScriptString* uscript_string_append(UScriptString *str1, UScriptString *str2);

//! Internal function to ensure all strings provided in arguments are initialized.
bool __ensure_uscript_string_initialized(int n_str, ...);

#endif