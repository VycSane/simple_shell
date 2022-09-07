#include "_allocs.h"
#include "_shell_utils.h"

/**
 * _realloc - adjusts memory of a malloc'd memory
 * @block: the specified block to readjust
 * @size: the new size
 *
 * Return: void pointer to the memory block, or NULL on error
 */
void *_realloc(void *block, size_t size)
{
	void *new_block;

	/* If old block is not NULL and size is zero, free the old block */
	if (block != NULL && size == 0)
	{
		free(block);
		block = NULL;
		return (block);
	}
	/* If old block is NULL, create a memory block of the specified size */
	if (block == NULL)
	{
		block = malloc(size);
		exit_on_alloc_fail(block, EXIT_FAILURE);
		return (block);
	}
	new_block = malloc(size);
	exit_on_alloc_fail(block, EXIT_FAILURE);
	_strcpy(new_block, block);
	free(block);
	return (new_block);
}
