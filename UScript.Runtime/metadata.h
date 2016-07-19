#ifndef METADATA_H
#define METADATA_H

#include <stdint.h>
#include <stdio.h>
#include "include/error.h"
#include "metadata_context.h"

USCRIPT_ERR create_mdctx_from_file(FILE *, UScriptMetadataContext **);

USCRIPT_ERR create_mdctx(char *, UScriptMetadataContext **);

USCRIPT_ERR parse_func_tbl(char *, FunctionMetadataTable **, UScriptMetadataContext *);

#endif
