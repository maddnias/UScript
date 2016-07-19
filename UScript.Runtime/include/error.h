#ifndef ERROR_H
#define ERROR_H

#include <errno.h>

#define USCRIPT_ERR int32_t

#define USCRIPT_ERR_SUCCESS 0
#define USCRIPT_ERR_INVALID_MAGIC 1
#define USCRIPT_ERR_FILE_ERR 2
#define USCRIPT_ERR_UNK 3
#define USCRIPT_ERR_UNKNOWN_OP 4
#define USCRIPT_ERR_STACK_OVERFLOW 5

#endif
