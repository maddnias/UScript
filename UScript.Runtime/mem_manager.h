#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H

#include <stdint.h>
#include "include/error.h"
#include <stdbool.h>

typedef struct MemoryFragment {
	uint32_t start_addr;
	uint32_t size;
} MemoryFragment;

typedef struct MemoryBlock {
	uint32_t fragment_count;
	MemoryFragment **fragments;
	char *block_data;
} MemoryBlock;

typedef struct FragmentRef {
	uint32_t hash;
	MemoryFragment *fragment;
} FragmentRef;

typedef struct MemoryManager {
	uint32_t tbl_size;
	FragmentRef **fragment_ref_tbl;
	MemoryBlock mem_block;
} MemoryManager;

USCRIPT_ERR mem_mgr_create(MemoryManager **mgr);

USCRIPT_ERR mem_mgr_destroy(MemoryManager *mgr);

USCRIPT_ERR mem_mgr_alloc(MemoryManager *mgr, uint32_t size, uint32_t *hash);

USCRIPT_ERR mem_mgr_free(MemoryManager *mgr, uint32_t hash);

USCRIPT_ERR mem_fragment_create(MemoryFragment **fragment);

USCRIPT_ERR mem_fragment_destroy(MemoryFragment *fragment);

USCRIPT_ERR __create_add_mem_fragment(MemoryManager *mgr, uint32_t size, uint32_t *hash);

USCRIPT_ERR __delete_mem_fragment(MemoryManager *mgr, uint32_t hash);

int32_t __fragment_exists(MemoryManager *mgr, uint32_t hash);

USCRIPT_ERR __find_mem_fragment(MemoryManager *mgr, uint32_t hash, FragmentRef **ref);

USCRIPT_ERR __find_empty_block(MemoryManager *mgr, uint32_t size, uint32_t *addr);

#endif
