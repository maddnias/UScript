#ifndef ERROR_H
#define ERROR_H

#include <errno.h>
#include <stdio.h>

#define USCRIPT_ERR int32_t

#define USCRIPT_ERR_SUCCESS 0
#define USCRIPT_ERR_INVALID_MAGIC 1
#define USCRIPT_ERR_FILE_ERR 2
#define USCRIPT_ERR_UNK 3
#define USCRIPT_ERR_UNKNOWN_OP 4
#define USCRIPT_ERR_STACK_OVERFLOW 5
#define USCRIPT_ERR_TOKEN_MISSING 6

//! Returns a zero-terminated string that includes full error message.
/*!
	\param[in] err The error code to translate.
	\return The translated error code.
*/
inline char* translate_err_code(USCRIPT_ERR err) {
	switch (err)
	{
	case USCRIPT_ERR_SUCCESS:
		return "USCRIPT_ERR_SUCCESS:\r\n\r\nUScript operation completed successfully.\0";
	case USCRIPT_ERR_INVALID_MAGIC:
		return "USCRIPT_ERR_INVALID_MAGIC:\r\n\r\nAn invalid magic number was parsed from the compiled script header. This usually indicates a corrupted or invalid file.\0";
	case USCRIPT_ERR_FILE_ERR:
		return "USCRIPT_ERR_FILE_ERR:\r\n\r\nFile related error.\0";
	case USCRIPT_ERR_UNK:
		return "USCRIPT_ERR_UNK:\r\n\r\nAn unknown error has occurred from which the script execution cannot continue.\0";
	case USCRIPT_ERR_UNKNOWN_OP:
		return "USCRIPT_ERR_UNKNOWN_OP:\r\n\r\nAn unknown opcode was parsed from the compiled script code section. This usually indicates a corrupted or invalid file.\0";
	}

	char buf[30];
	sprintf_s(buf, 30, "Unknown error code: %i\0", (int32_t)err);
	return buf;
}

#endif
