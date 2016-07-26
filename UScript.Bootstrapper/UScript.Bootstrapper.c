// UScript.Bootstrapper.cpp : Defines the entry point for the console application.
//
#include "metadata.h"
#include "executor.h"



int main()
{
	getchar();
	FILE *fp;
	fp = fopen("C:\\Users\\mattias\\Documents\\compiled_script.usce", "rb");

	UScriptMetadataContext *mdCtx;
	create_mdctx_from_file(fp, &mdCtx);

	UScriptRuntimeContext *ctx;
	runtime_ctx_create(&ctx, mdCtx);

	while (execute_next(ctx) == USCRIPT_ERR_SUCCESS) {
	}

	printf("%i", *(int32_t*)ctx->cur_frame->func_ctx->eval_stack->entries[0]->obj->data);
	getchar();
    return 0;
}

