#include "shell.h"
/**
 * _strncpy - Function copies the strings
 * @dest: The destination string to be copied
 * @src: The source of the string
 * @n: The amount of the charcter to be copied
 *
 * Return: conacted string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int s, r;
	char *c = dest;

	s = 0;
	while (src[s] != '\0' && s < n - 1)
	{
		dest[s] = src[s];
		s++;
	}
	if (s < n)
	{
		r = s;
		while (r < n)
		{
			dest[r] = '\0';
			r++;
		}
	}
	return (c);
}
/**
 * _strncat - The function conacted two strings
 * @dest: The first string
 * @src: The second Strings
 * @n: The amount of the bytes tobe used
 *
 * Return: Conacted string
 */
char *_strncat(char *dest, char *src, int n)
{
	int s, r;
	char *c = dest;

	s = 0;
	r = 0;
	while (dest[s] != '\0')
		s++;
	while (src[r] != '\0' && r < n)
	{
		dest[s] = src[r];
		s++;
		r++;
	}
	if (r < n)
		dest[s] = '\0';
	return (c);
}
/**
 * _strchr - Locate the charcter in the string
 * @s: The string
 * @c: The Charcter
 *
 * Return: (s) a pointer to the memory s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

