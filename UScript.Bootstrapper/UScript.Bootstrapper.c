// UScript.Bootstrapper.cpp : Defines the entry point for the console application.
//
#include "metadata.h"
#include "executor.h"



int main()
{
	FILE *fp;
	fp = fopen("C:\\compiled_script.usce", "rb");

	auto lol = translate_err_code(2);

	UScriptMetadataContext *mdCtx;
	create_mdctx_from_file(fp, &mdCtx);

	UScriptRuntimeContext *ctx;
	runtime_ctx_create(&ctx, mdCtx);

	while (true) {
		execute_next(ctx);
	}

    return 0;
}

