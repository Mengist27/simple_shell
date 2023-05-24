#include "shell.h"
#include <string.h>
#include <stdio.h>

#define BUF_FLUSH '\0'

/**
 * _strcpy - copies a string
 * @dest: The destination
 * @src: The source
 *
 * Return: pointers to be destinations
 */
char *_strcpy(char *dest, char *src)
{
	int u = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[u])
	{
		dest[u] = src[u];
		u++;
	}
	dest[u] = 0;
	return (dest);
}

/**
 * _strdup - duplicates the string
 * @str: The string to be duplicate
 *
 * Return: pointers to be the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - prints an input the string
 * @str: The string to be print
 *
 * Return: nothing
 */
void _puts(char *str)
{
	int u = 0;

	if (!str)
		return;
	while (str[u] != '\0')
	{
		_putchar(str[u]);
		u++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int u;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || u >= WRITE_BUF_SIZE)
	{
		write(1, buf, u);
		u = 0;
	}
	if (c != BUF_FLUSH)
		buf[u++] = c;
	return (1);
}
