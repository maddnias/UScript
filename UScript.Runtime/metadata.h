#ifndef METADATA_H
#define METADATA_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "include/error.h"
#include "include/uscript_string.h"

static const int64_t HDR_MAGIC = 0x0BBE1010BBE101;
static const int64_t FUNCTION_TOK_BASE = 0x10000000;
static const int64_t STRING_TOK_BASE = 0x20000000;

struct UScriptPEHeader {
	int64_t magic;
	uint64_t code_start;
	uint64_t function_tbl_addr;
	uint64_t string_tbl_addr;
	uint64_t blob_addr;
};

struct FunctionMetadataRow {
	int64_t token;
	struct UScriptString name;
	bool ep;
	uint64_t blob_addr;
	uint64_t code_addr;
};

struct FunctionMetadataTable {
	int32_t func_count;
	struct FunctionMetadataRow** tbl;
};

struct UScriptMetadataContext {
	struct UScriptPEHeader pe_hdr;
	struct FunctionMetadataTable func_tbl;
};

USCRIPT_ERR
create_mdctx_from_file(FILE *, struct UScriptMetadataContext **);

USCRIPT_ERR
create_mdctx(char *, struct UScriptMetadataContext **);

USCRIPT_ERR
parse_func_tbl(char *, struct FunctionMetadataTable **, struct UScriptMetadataContext *);

#endif
