#include "uscript_string.h"
#include <stdlib.h>
#include <memory.h>

struct UScriptString* alloc_uscript_string(int32_t str_len) {
	struct UScriptString *str;
	str = (struct UScriptString*)malloc(sizeof(int32_t) + str_len + sizeof(bool));
	str->len = str_len;
	str->initialized = false;

	return str;
}

struct UScriptString* create_uscript_string(int32_t str_len, char *data) {
	struct UScriptString *str = alloc_uscript_string(str_len);
	set_uscript_string_data(&str, data);

	return str;
}

void set_uscript_string_data(struct UScriptString **str, char *data) {
	// Immutable
	if((*str)->initialized) {
		return;
	}

	(*str)->data = (char*)malloc((*str)->len);
	memcpy((*str)->data, data, (*str)->len);

	(*str)->initialized = true;
}

void destroy_uscript_string(struct UScriptString *str) {
	free(str->data);
}

bool uscript_string_is_equal(struct UScriptString *str1, struct UScriptString *str2) {
	if (!str1->initialized || !str2->initialized)
		return false;

	if (str1->len != str2->len)
		return false;

	for (int i = 0; i < str1->len; i++)
		if (str1->data[i] != str2->data[i])
			return false;

	return true;
}