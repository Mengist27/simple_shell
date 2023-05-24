#include "shell.h"

/**
 * bfree - frees the pointers and NULLs the address
 * @ptr: the address of the pointers to be free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
