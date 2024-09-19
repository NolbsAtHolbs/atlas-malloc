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
	static void *current_brk = NULL;
	static void *heap_end = NULL;

	size_t qpu_aligned = (((size + 7) / 8) * 8); /* aligns size to 8 bytes*/
	size_t total_size = qpu_aligned + sizeof(size_t); /* include space for header */
	size_t page_size = sysconf(_SC_PAGESIZE); /* gets default system page size */
	size_t num_pages = ((total_size + page_size - 1) / page_size); /* calculate required pages */
	size_t alloc_size = num_pages * page_size; /* total allocation size */

	if (current_brk == NULL)
	{
		current_brk = sbrk(0);
		heap_end = current_brk;
	}

	if ((char *)current_brk + total_size > (char *)heap_end)
    {
		/* extend the heap */
		size_t alloc_size = ((total_size + page_size - 1) / page_size) * page_size;

		void *result = sbrk(alloc_size); /* now extend program break */

		if (result == (void *)-1) /* sbrk allocation failure */
		{
			errno = ENOMEM;
			return (NULL);
		}

		heap_end = (char *)heap_end + alloc_size;
	}

	/* store the aligned size in the header to assist with memory management */
	*((size_t *)current_brk) = qpu_aligned;

	/* return a pointer to user-accessible memory area, after block size header */
	void *user_ptr = (void *)((char *)current_brk + sizeof(size_t));

	/* advance current_brk */
	current_brk = (char *)current_brk + total_size;

	return (user_ptr);
}
