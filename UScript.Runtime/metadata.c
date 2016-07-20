#include "metadata.h"
#include <stdlib.h>
#include "uscript_string.h"
#include <memory.h>

//! Creates a metadata context from a file
/*!
	\param[in] file The file handle to read from.
	\param[out] The metadata context.
*/
USCRIPT_ERR create_mdctx_from_file(FILE *file,  UScriptMetadataContext** ctx)
{
	if (file == NULL)
		return USCRIPT_ERR_FILE_ERR;

	fseek(file, 0, SEEK_END);
	int64_t fileSize = ftell(file);

	if (fileSize < sizeof( UScriptPEHeader))
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

	(*ctx)->code_block_size = fileSize - (*ctx)->pe_hdr.code_start;
	(*ctx)->code_block = (char*)malloc((*ctx)->code_block_size);

	memcpy((*ctx)->code_block, buf + (*ctx)->pe_hdr.code_start, (*ctx)->code_block_size);

	free(buf);
	return USCRIPT_ERR_SUCCESS;
}

//! Creates a metadata context from a buffer
/*!
	\param[in] buf The buffer containing the metadata context.
	\param[out] ctx The metadata context.
*/
USCRIPT_ERR create_mdctx(char *buf,  UScriptMetadataContext **ctx)
{
	if (buf == NULL)
		return USCRIPT_ERR_FILE_ERR;

	*ctx = ( UScriptMetadataContext*)malloc(sizeof( UScriptMetadataContext));
	**ctx = *( UScriptMetadataContext*)buf;

	if((*ctx)->pe_hdr.magic != HDR_MAGIC) {
		free(ctx);
		return USCRIPT_ERR_INVALID_MAGIC;
	}

	buf += sizeof( UScriptPEHeader);

	USCRIPT_ERR res;
	 FunctionMetadataTable *func_tbl;
	if((res = parse_func_tbl(buf, &func_tbl, *ctx)) != USCRIPT_ERR_SUCCESS) {
		free(ctx);
		return USCRIPT_ERR_UNK;
	}

	(*ctx)->func_tbl = *func_tbl;

	return USCRIPT_ERR_SUCCESS;
}

//! Parses a function table from the current position in a buffer.
/*!
	\param[in] buf The buffer that contains the function table.
	\param[out] tbl The function table.
	\param[in] ctx The metadata context to use.
*/
USCRIPT_ERR parse_func_tbl(char *buf, FunctionMetadataTable** tbl, UScriptMetadataContext *ctx)
{
	int32_t funcCount = sizeof( FunctionMetadataRow)
		/ (ctx->pe_hdr.string_tbl_addr - ctx->pe_hdr.function_tbl_addr);

	 FunctionMetadataRow** pRowArr = 
		( FunctionMetadataRow**)malloc(funcCount * sizeof( FunctionMetadataRow*));

	for(int i = 0;i < funcCount;i++) {
		pRowArr[i] = ( FunctionMetadataRow*)malloc(sizeof( FunctionMetadataRow));
		pRowArr[i]->token = i + FUNCTION_TOK_BASE;

		uscript_datatype returnType = (uscript_datatype)*(char*)buf;
		UScriptTypeDesc *returnTypeDesc;
		type_desc_create(&returnTypeDesc, returnType);
		pRowArr[i]->return_type = returnTypeDesc;
		buf++;

		int32_t nameLen = *(int32_t*)buf;// UScriptString *strName = uscript_string_alloc(*(int32_t*)buf);
		buf += sizeof(int32_t);
		
		//uscript_string_set_data(&strName, buf);
		pRowArr[i]->name = uscript_string_create(nameLen, buf);
		buf += pRowArr[i]->name->len;

		pRowArr[i]->ep = *(char*)buf;
		buf++;

		pRowArr[i]->blob_addr = *(int64_t*)buf;
		buf += sizeof(int64_t);

		pRowArr[i]->code_addr = *(int64_t*)buf;
		buf += sizeof(int64_t);
	}

	*tbl = ( FunctionMetadataTable*)malloc(sizeof( FunctionMetadataTable));
	(*tbl)->func_count = funcCount;
	(*tbl)->tbl = pRowArr;

	return USCRIPT_ERR_SUCCESS;
}

//TODO: error handling
//! Resolves a function token and returns it's metadata row.
/*!
	\param[out] row The row.
	\param[in] ctx The metadata context.
	\param[in] token The token to resolve.
*/
USCRIPT_ERR resolve_func_token(FunctionMetadataRow **row, UScriptMetadataContext *ctx, int32_t token) {
	*row = ctx->func_tbl.tbl[token - FUNCTION_TOK_BASE];

	return USCRIPT_ERR_SUCCESS;
}
