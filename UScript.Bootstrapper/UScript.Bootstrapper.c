// UScript.Bootstrapper.cpp : Defines the entry point for the console application.
//
#include "metadata.h"


int main()
{
	FILE *fp;
	fp = fopen("C:\\compiled_script.usce", "rb");


	struct UScriptMetadataContext *mdCtx;
	create_mdctx_from_file(fp, &mdCtx);

    return 0;
}

