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
/*!
	\param[in] str_len The length of the string data.

	\return An uninitialized uscript_string, set data with 
	
	\sa uscript_string_set_data
*/
UScriptString* uscript_string_alloc(int32_t);

//! Creates a uscript_string and sets the data.
/*!
	\param[in] str_len The length of the string.
	\param[in] data The data of the string.

	\return The newly created string.
*/
UScriptString* uscript_string_create(int32_t, char *);

//! Set the string data in an uscript_string.
/*!
	\param[in] str The string on which the data is set.
	\param[in] data The string data.

	\sa uscript_string_create
*/
void uscript_string_set_data(UScriptString *str, char *data);

//! Destroys an uscript_string.
/*!
	\param[in] str The string to destroy.
*/
void uscript_string_destroy(UScriptString *str);

//! Checks if two uscript_strings are equal to each other.
/*!
	\param[in] str1 The first string.
	\param[in] str2 The second string.

	\return A boolean indicating whether or not the strings are equal
*/
bool uscript_string_is_equal(UScriptString *str1, UScriptString *str2);

//! Appends two uscript_strings into one.
/*!
	\param[in] str1 The first string.
	\param[in] str2 The second string.

	\return The concatenated string.
*/
UScriptString* uscript_string_append(UScriptString *str1, UScriptString *str2);

//! Internal function to ensure all strings provided in arguments are initialized.
/*!
	\param[in] n_str The amount of strings to check.

	\return A boolean indicating whether or not all strings are initialized.
*/
bool __ensure_uscript_string_initialized(int n_str, ...);

#endif