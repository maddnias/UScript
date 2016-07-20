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

#endif
