// UScript.Bootstrapper.cpp : Defines the entry point for the console application.
//
#include "metadata.h"
#include "executor.h"


int main()
{
	FILE *fp;
	fp = fopen("C:\\compiled_script.usce", "rb");


	UScriptMetadataContext *mdCtx;
	create_mdctx_from_file(fp, &mdCtx);

	UScriptRuntimeContext *ctx;
	create_runtime_ctx(&ctx, mdCtx);

	while (true) {
		execute_next(ctx);
	}

    return 0;
}

