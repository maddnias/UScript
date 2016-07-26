#include "mem_manager.h"
#include <stdlib.h>
#include "superfasthash.h"

USCRIPT_ERR mem_mgr_create(MemoryManager** mgr) {
	*mgr = (MemoryManager*)malloc(sizeof(MemoryManager));
	(*mgr)->mem_block.block_data = (char*)malloc(4096 /* TODO: customize */);

	return USCRIPT_ERR_SUCCESS;
}

USCRIPT_ERR mem_mgr_destroy(MemoryManager* mgr) {
	for(int i = 0;i < mgr->tbl_size;i++) {
		free(mgr->fragment_ref_tbl[i]);
	}
	free(mgr->fragment_ref_tbl);

	return USCRIPT_ERR_SUCCESS;
}

USCRIPT_ERR mem_fragment_create(MemoryFragment** fragment) {
	*fragment = (MemoryFragment*)malloc(sizeof(MemoryFragment));
	(*fragment)->size = 0;
	(*fragment)->start_addr = 0;

	return USCRIPT_ERR_SUCCESS;
}

USCRIPT_ERR mem_fragment_destroy(MemoryFragment* fragment) {
	free(fragment);

	return USCRIPT_ERR_SUCCESS;
}

USCRIPT_ERR __create_add_mem_fragment(MemoryManager *mgr, uint32_t size, uint32_t *hash) {
	MemoryFragment *fragment;
	mem_fragment_create(&fragment);

	fragment->size = size;

	return USCRIPT_ERR_SUCCESS;
}

int32_t __fragment_exists(MemoryManager* mgr, uint32_t hash) {
	for(int i = 0;i < mgr->tbl_size;i++) {
		if(mgr->fragment_ref_tbl[i]->hash == hash) {
			return i;
		}
	}

	return -1;
}

USCRIPT_ERR __find_mem_fragment(MemoryManager *mgr, uint32_t hash, FragmentRef** ref) {
	int32_t idx = __fragment_exists(mgr, hash);

	if(idx < 0) {
		// not found
		return USCRIPT_ERR_SUCCESS;
	}
	
	*ref = mgr->fragment_ref_tbl[idx];

	return USCRIPT_ERR_SUCCESS;
}