#include "shell.h"

/**
 * _strlen - returns the lengths of the string
 * @s: The string whose length to the checker
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int p = 0;

	if (!s)
		return (0);

	while (s++)
		p++;
	return (p);
}

/**
 * _strcmp - performs lexicogarphic comparison of the two strangs.
 * @s1: The 1st strang
 * @s2: The 2nd strang
 *
 * Return: Negative when s1 < s2, positive when s1 > s2, zero when s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks when needle starts with haystack
 * @haystack: String to be searching
 * @needle: The substring to find
 *
 * Return: address of the next char of the haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates on two strings
 * @dest: shows The destination buffers
 * @src: shows the source buffer
 *
 * Return: pointers to be destination buffers
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
