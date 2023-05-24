#include "shell.h"
/**
 * _eputs - The function to prints an input string
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int s = 0;

	if (!str)
		return;
	while (str[s] != '\0')
	{
		_eputchar(str[s]);
		s++;
	}
}
/**
 * _eputchar - THe function to write the character c to stderr
 * @c: The Character to be printed
 *
 * Return: 1 on success, -1 on error and errno set appropriately
 */
int _eputchar(char c)
{
	static int s;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || s >= WRITE_BUF_SIZE)
	{
		write(2, buf, s);
		s = 0;
	}
	if (c != BUF_FLUSH)
		buf[s++] = c;
	return (1);
}
/**
 * _putfd - The function write the character of c to given fd
 * @c: THe charcter to be printed
 * @fd: The File Descriptor to write too
 *
 * Return: 1 on success, -1 on error
 */
int _putfd(char c, int fd)
{
	static int s;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || s >= WRITE_BUF_SIZE)
	{
		write(fd, buf, s);
		s = 0;
	}
	if (c != BUF_FLUSH)
		buf[s++] = c;
	return (1);
}
/**
 * _putsfd - to prints an input strings
 * @str: The string to be printed
 * @fd: The File Descriptor to write too
 *
 * Return: The Num of charcters put
 */
int _putsfd(char *str, int fd)
{
	int s = 0;

	if (!str)
		return (0);
	while (*str)
	{
		s += _putfd(*str++, fd);
	}
	return (s);
}

