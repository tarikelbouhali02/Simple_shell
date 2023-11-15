#include "shell.h"

/**
 * ta_realloc -to  Reallocates  memory block
 * @ptr: Pointer to the memory at be reallocated
 * @old_size: Size in bytes to the actual allocated memory
 * @new_size: Size in bytes for  new allocated memory
 *
 * Return:Pointer to  newly allocated memory
 */
void *ta_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	int tlimit, t;
	void *pointer;

	if (old_size == new_size)
		return (ptr);

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	pointer = malloc(new_size);

	if (old_size > new_size)
		tlimit = new_size;
	else
		tlimit = old_size;

	for (t = 0; t < tlimit; t++)
		((char *)pointer)[t] = ((char *)ptr)[t];

	free(ptr);

	return (pointer);
}
