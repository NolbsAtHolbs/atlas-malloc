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
	size_t qpu_aligned = (((size + 7) / 8) * 8); /* aligns size to 8 bytes*/
	size_t total_size = qpu_aligned + sizeof(size_t); /* include space for header */
	size_t page_size = sysconf(_SC_PAGESIZE); /* gets default system page size */
	size_t num_pages = ((total_size + page_size - 1) / page_size); /* calculate required pages */
	size_t alloc_size = num_pages * page_size; /* total allocation size */
	
	void *allocated_memory = sbrk(alloc_size); /* extend program break */

	if (allocated_memory == (void *)-1) /* sbrk allocation failure */
	{
		errno = ENOMEM;
		return (NULL);
	}

	/* store the aligned size in the header to assist with memory management */
	*((size_t *)allocated_memory) = qpu_aligned;

	/* return a pointer to user-accessible memory area, after block size hdr */
	return (void *)((char *)allocated_memory + sizeof(size_t));

}
