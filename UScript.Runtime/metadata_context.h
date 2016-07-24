#ifndef METADATA_CONTEXT_H
#define METADATA_CONTEXT_H

#include <stdint.h>
#include <stdbool.h>
#include "include/uscript_string.h"
#include "data_types.h"

static const int64_t HDR_MAGIC = 0x0BBE1010BBE101;
static const int32_t FUNCTION_TOK_BASE = 0x1000;
static const int32_t STRING_TOK_BASE = 0x2000;

typedef struct UScriptPEHeader {
	int64_t magic;
	uint64_t code_start;
	uint64_t function_tbl_addr;
	uint64_t string_tbl_addr;
	uint64_t blob_addr;
} UScriptPEHeader;

typedef struct FunctionMetadataRow {
	UScriptTypeDesc *return_type;
	int32_t token;
	int32_t param_count;
	UScriptTypeDesc **param_descriptors;
	char *name;
	bool ep;
	uint64_t blob_addr;
	uint64_t code_addr;
	uint64_t code_relative_addr;
} FunctionMetadataRow;

typedef struct FunctionMetadataTable {
	int32_t func_count;
	struct FunctionMetadataRow** tbl;
} FunctionMetadataTable;

typedef struct UScriptMetadataContext {
	UScriptPEHeader pe_hdr;
	FunctionMetadataTable func_tbl;
	int32_t blob_block_size;
	char* blob_block;
	int32_t entry_code_block_size;
	int32_t code_block_size;
	char* code_block;
} UScriptMetadataContext;

#endif