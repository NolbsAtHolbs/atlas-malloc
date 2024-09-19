#ifndef MALLOC_H
#define MALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

void *naive_malloc(size_t size);
void *_malloc(size_t size);
void _free(void *ptr);

/**
 * data_block_t - typedef for struct data_block
 *
 * makes an alias for `struct data_block` called `data_block_t`.
 * allows for convenient reference to the struct type.
 */
typedef struct data_block data_block_t;

/**
 * struct data_block - represents a block of memory in the custom allocator
 * @size: size of the data block in bytes
 * @free_flag: flag indicating if the block is free or allocated
 * @next: ptr to next data block in linked list
 *
 * this structure is used to manage memory blocks for _malloc.
 * blocks contain info about the size, status, and a ptr to the next block,
 * so it is a linked list of memory blocks.
 */
struct data_block
{
	size_t size;
	int free_flag;
	data_block_t *next;
};

#define DBS sizeof(data_block_t)

extern data_block_t *global_free_list;

#endif
