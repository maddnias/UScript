#include "uscript_string.h"
#include <stdlib.h>
#include <memory.h>
#include <stdarg.h>

//! Allocates memory for a new uscript_string.
/*!
	\param[in] str_len The length of the string data.

	\return An uninitialized uscript_string, set data with {\sa uscript_string_set_data}.
*/
UScriptString* uscript_string_alloc(int32_t str_len) {
	UScriptString *str;
	str = ( UScriptString*)malloc(sizeof(int32_t) + str_len + sizeof(bool));
	str->len = str_len;
	str->initialized = false;

	return str;
}

//! Creates a uscript_string and sets the data.
/*!
	\param[in] str_len The length of the string.
	\param[in] data The data of the string.

	\return The newly created string.
*/
 UScriptString* uscript_string_create(int32_t str_len, char *data) {
	UScriptString *str = uscript_string_alloc(str_len);
	uscript_string_set_data(str, data);

	return str;
}

//! Set the string data in an uscript_string.
/*!
	\param[in] str The string on which the data is set.
	\param[in] data The string data.

	\remark
		Will fail if the uscript_string is not initialized. {\sa uscript_string_create}
*/
void uscript_string_set_data( UScriptString *str, char *data) {
	// Immutable
	if(str->initialized) {
		return;
	}

	str->data = (char*)malloc(str->len);
	memcpy(str->data, data, str->len);

	str->initialized = true;
}

//! Destroys an uscript_string.
/*!
	\param[in] str The string to destroy.
*/
void uscript_string_destroy( UScriptString *str) {
	free(str->data);
}

//! Checks if two uscript_strings are equal to each other.
/*!
	\param[in] str1 The first string.
	\param[in] str2 The second string.

	\return A boolean indicating whether or not the strings are equal
*/
bool uscript_string_is_equal( UScriptString *str1,  UScriptString *str2) {
	if (!__ensure_uscript_string_initialized(2, str1, str2)) {
		return false;
	}

	if (str1->len != str2->len)
		return false;

	for (int i = 0; i < str1->len; i++)
		if (str1->data[i] != str2->data[i])
			return false;

	return true;
}

//! Appends two uscript_strings into one.
/*!
	\param[in] str1 The first string.
	\param[in] str2 The second string.

	\return The concatenated string.

	\remark
		str1 and str2 are destroyed in the process.
*/
UScriptString* uscript_string_append(UScriptString *str1, UScriptString *str2) {
	if (!__ensure_uscript_string_initialized(2, str1, str2)) {
		return NULL;
	}

	int32_t newLen = str1->len + str2->len;

	char *dat = (char*)malloc(newLen);
	memcpy(dat, str1->data, str1->len);
	memcpy(dat + str1->len, str2->data, str2->len);

	UScriptString *strNew = uscript_string_create(newLen, dat);
	free(dat);

	uscript_string_destroy(str1);
	uscript_string_destroy(str2);

	return strNew;
}

//! Internal function to ensure all strings provided in arguments are initialized.
/*!
	\param[in] n_str The amount of strings to check.

	\return A boolean indicating whether or not all strings are initialized.
*/
bool __ensure_uscript_string_initialized(int n_str, ...) {
	va_list ap;
	va_start(ap, n_str);
	
	for(int i = 0;i < n_str;i++) {
		if (!va_arg(ap, UScriptString*)->initialized)
			return false;
	}

	va_end(ap);
	return true;
 }