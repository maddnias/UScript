#include "uscript_string.h"
#include <stdlib.h>
#include <memory.h>

 UScriptString* alloc_uscript_string(int32_t str_len) {
	 UScriptString *str;
	str = ( UScriptString*)malloc(sizeof(int32_t) + str_len + sizeof(bool));
	str->len = str_len;
	str->initialized = false;

	return str;
}

 UScriptString* create_uscript_string(int32_t str_len, char *data) {
	 UScriptString *str = alloc_uscript_string(str_len);
	set_uscript_string_data(&str, data);

	return str;
}

void set_uscript_string_data( UScriptString **str, char *data) {
	// Immutable
	if((*str)->initialized) {
		return;
	}

	(*str)->data = (char*)malloc((*str)->len);
	memcpy((*str)->data, data, (*str)->len);

	(*str)->initialized = true;
}

void destroy_uscript_string( UScriptString *str) {
	free(str->data);
}

bool uscript_string_is_equal( UScriptString *str1,  UScriptString *str2) {
	if (!str1->initialized || !str2->initialized)
		return false;

	if (str1->len != str2->len)
		return false;

	for (int i = 0; i < str1->len; i++)
		if (str1->data[i] != str2->data[i])
			return false;

	return true;
}