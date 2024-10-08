#include "malloc.h"

static data_block_t *global_free_list; /* = NULL */

/**
 * locate_free_block - locates a free block to accomodate the requested size
 * @last: double ptr to the last block inspected during traversal
 * @size: size of memory fit to request
 * Return: ptr to suitable free block if successfully found, else NULL
 */
data_block_t *locate_free_block(data_block_t **last, size_t size)
{
	data_block_t *current = global_free_list;

	while (current)
	{
		if (current->free_flag && current->size >= size)
			return (current);

		*last = current;
		current = current->next;
	}
	return (NULL);
}

/**
 * request_space - asks for more memory from system using sbrk
 * @last: ptr to last block in linked list
 * @size: size of list
 * Return: ptr to newly allocated block if success, else NULL
 */
data_block_t *request_space(data_block_t *last, size_t size)
{
	data_block_t *block;

	block = sbrk(0);
	void *request = sbrk(size + DBS);

	if (request == (void *)-1)
	{
		errno = ENOMEM;
		return (NULL);
	}

	if (last)
		last->next = block;

	block->size = size;
	block->free_flag = 0;
	block->next = NULL;

	return (block);
}

/**
 * _malloc - allocates `size` bytes from heap, adjusts size of heap as required
 * @size: size needed to be allocated for the user
 * Return: ptr to allocated memory that is suitably aligned for any kind of var
 */
void *_malloc(size_t size)
{
	data_block_t *block;
	size_t aln;

	if (size == 0)
		return (NULL);
	aln = (((size + 7) / 8) * 8);
	if (!global_free_list)
	{
		block = request_space(NULL, aln);
		if (!block)
			return (NULL);
		global_free_list = block;
	}
	else
	{
		data_block_t *last = global_free_list;

		block = locate_free_block(&last, aln);
		if (!block)
		{
			block = request_space(last, aln);
			if (!block)
				return (NULL);
		}
		else
		{
			if (block->size >= aln + 2 * DBS + 8)
			{
				data_block_t *nb = (data_block_t *)((char *)block + aln + DBS);

				nb->size = block->size - (aln + DBS);
				nb->free_flag = 1;
				nb->next = block->next;
				block->size = aln;
				block->next = nb;
			}
			block->free_flag = 0;
		}
	}
	return ((void *)(block + 1));
}
