#ifndef METADATA_H
#define METADATA_H

#include <stdint.h>
#include <stdio.h>
#include "include/error.h"
#include "metadata_context.h"

//! Creates a metadata context from a file
	/*!
	\param[in] file The file handle to read from.
	\param[out] The metadata context.
*/
USCRIPT_ERR create_mdctx_from_file(FILE *, UScriptMetadataContext **);

//! Creates a metadata context from a buffer
/*!
	\param[in] buf The buffer containing the metadata context.
	\param[out] ctx The metadata context.
*/
USCRIPT_ERR create_mdctx(char *, UScriptMetadataContext **);

//! Parses a function table from the current position in a buffer.
/*!
	\param[in] buf The buffer that contains the function table.
	\param[out] tbl The function table.
	\param[in] ctx The metadata context to use.
*/
USCRIPT_ERR parse_func_tbl(char *, FunctionMetadataTable **, UScriptMetadataContext *);

#endif
