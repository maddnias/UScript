#include "metadata.h"
#include <stdlib.h>
#include "helper.h"
#include <memory.h>
#include "include/uscript_string.h"

USCRIPT_ERR create_mdctx_from_file(FILE *file, struct UScriptMetadataContext** ctx)
{
	if (file == NULL)
		return USCRIPT_ERR_FILE_ERR;

	fseek(file, 0, SEEK_END);
	int64_t fileSize = ftell(file);

	if (fileSize < sizeof(struct UScriptPEHeader))
		return USCRIPT_ERR_FILE_ERR;

	rewind(file);

	char* buf = (char*)malloc(fileSize);
	
	if(fread(buf, sizeof(char), fileSize, file) != fileSize) {
		free(buf);
		return USCRIPT_ERR_FILE_ERR;
	}

	USCRIPT_ERR res;

	if((res = create_mdctx(buf, ctx)) != USCRIPT_ERR_SUCCESS) {
		free(buf);
		return res;
	}

	free(buf);
	return USCRIPT_ERR_SUCCESS;
}

USCRIPT_ERR create_mdctx(char *buf, struct UScriptMetadataContext **ctx)
{
	if (buf == NULL)
		return USCRIPT_ERR_FILE_ERR;

	*ctx = (struct UScriptMetadataContext*)malloc(sizeof(struct UScriptMetadataContext));
	**ctx = *(struct UScriptMetadataContext*)buf;

	if((*ctx)->pe_hdr.magic != HDR_MAGIC) {
		free(ctx);
		return USCRIPT_ERR_INVALID_MAGIC;
	}

	buf += sizeof(struct UScriptPEHeader);

	USCRIPT_ERR res;
	struct FunctionMetadataTable *func_tbl;
	if((res = parse_func_tbl(buf, &func_tbl, *ctx)) != USCRIPT_ERR_SUCCESS) {
		free(ctx);
		return USCRIPT_ERR_UNK;
	}

	(*ctx)->func_tbl = *func_tbl;

	return USCRIPT_ERR_SUCCESS;
}

USCRIPT_ERR parse_func_tbl(char *buf, struct FunctionMetadataTable** tbl, struct UScriptMetadataContext *ctx)
{
	int32_t funcCount = sizeof(struct FunctionMetadataRow)
		/ (ctx->pe_hdr.string_tbl_addr - ctx->pe_hdr.function_tbl_addr);

	struct FunctionMetadataRow** pRowArr = 
		(struct FunctionMetadataRow**)malloc(funcCount * sizeof(struct FunctionMetadataRow*));

	for(int i = 0;i < funcCount;i++) {
		pRowArr[i] = (struct FunctionMetadataRow*)malloc(sizeof(struct FunctionMetadataRow));
		pRowArr[i]->token = i + FUNCTION_TOK_BASE;

		struct UScriptString *strName = alloc_uscript_string(*(int32_t*)buf);
		buf += sizeof(int32_t);
		
		set_uscript_string_data(&strName, buf);
		pRowArr[i]->name = *strName;
		buf += pRowArr[i]->name.len;

		pRowArr[i]->ep = *(char*)buf;
		buf++;

		pRowArr[i]->blob_addr = *(int64_t*)buf;
		buf += sizeof(int64_t);

		pRowArr[i]->code_addr = *(int64_t*)buf;
		buf += sizeof(int64_t);
	}

	*tbl = (struct FunctionMetadataTable*)malloc(sizeof(struct FunctionMetadataTable));
	(*tbl)->func_count = funcCount;
	(*tbl)->tbl = pRowArr;

	return USCRIPT_ERR_SUCCESS;
}