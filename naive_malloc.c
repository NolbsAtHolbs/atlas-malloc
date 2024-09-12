#include "malloc.h"

/**
 * naive_malloc - allocates `size` bytes from the heap, and adjusts size of the
 * heap as required
 * @size: size needed to be allocated for the user
 * Return: pointer to the allocated memory that is suitably aligned
 * for any kind of variable
 */
void *naive_malloc(size_t size)
{
	size_t qpu_aligned = (((size + 7) / 8) * 8);

	return;
}