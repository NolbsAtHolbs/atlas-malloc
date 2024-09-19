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

/* declaration before defining struct. `data_block_t` is a type representing
	`struct data_block` */
typedef struct data_block data_block_t;

struct data_block {
	size_t size;
	int free_flag;
	data_block_t *next;
};

#define DATA_BLOCK_SIZE sizeof(data_block_t)

#endif
