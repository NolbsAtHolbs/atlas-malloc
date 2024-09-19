#include "malloc.h"

extern data_block_t *global_free_list;

/**
 * _free - frees the memory space pointed to by
 * @ptr: pointer to the memory space to be freed
 */
void _free(void *ptr)
{
	data_block_t *block;

	if (ptr == NULL)
		return;

	block = (data_block_t *)ptr - 1;

	block->free_flag = 1;
}
