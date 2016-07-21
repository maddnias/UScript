#ifndef METADATA_H
#define METADATA_H

#include <stdint.h>
#include <stdio.h>
#include "include/error.h"
#include "metadata_context.h"

//! Creates a metadata context from a file
USCRIPT_ERR create_mdctx_from_file(FILE *, UScriptMetadataContext **);

//! Creates a metadata context from a buffer
USCRIPT_ERR create_mdctx(char *, UScriptMetadataContext **);

//! Parses a function table from the current position in a buffer.
USCRIPT_ERR parse_func_tbl(char *, FunctionMetadataTable **, UScriptMetadataContext *);

USCRIPT_ERR parse_function_blob_data(char *blob, FunctionMetadataRow *funcRow);

//! Resolves a function token and returns it's metadata row.
USCRIPT_ERR resolve_func_token(FunctionMetadataRow **row, UScriptMetadataContext *ctx, int32_t token);

//! 
USCRIPT_ERR read_func_arg_type(FunctionMetadataRow *row, int32_t idx, UScriptTypeDesc **desc);

#endif
