#include "shell.h"

/**
 * _memset - fills memory with the constants byte
 * @s: The pointers to be the memory areas
 * @b: The bytes to be fill *s with
 * @n: The amounts of bytes to be filled
 * Return: (s) a pointers to the memory areas
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int u;

	for (u = 0; u < n; u++)
		s[u] = b;
	return (s);
}

/**
 * ffree - frees the string of strings
 * @pp: the string of strings
 */
void ffree(char **pp)
{
	char **z = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(z);
}

/**
 * fffree - frees the string of strings
 * @pp: string of strings
 */
void fffree(char **pp)
{
	char **z = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(z);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointers to be the previous malloc'ated blocks
 * @old_size: bytes size of the previous blocks
 * @new_size: bytes of the size of new block
 *
 * Return: pointers to be da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *q;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	q = malloc(new_size);
	if (!q)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		q[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (q);
}

