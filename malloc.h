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

#endif