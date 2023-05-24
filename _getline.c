#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * input_buf - the channel commands of buffer
 * @info: Parameter of the structs
 * @len: The addresses of the len variables
 * @buf: The addresses of the buffer
 * Return: The read of the bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t q = 0;
	size_t len_m = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		q = getline(buf, &len_p, stdin);
#else
		q = _getline(info, buf, &len_m);
#endif
		if (q > 0)
		{
			if ((*buf)[q - 1] == '\n')
			{
				(*buf)[q - 1] = '\0'; /* remove trailing newline */
				q--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = q;
				info->cmd_buf = buf;
			}
		}
	}
	return (q);
}
/**
 * get_input - gets the line of minus the new lines
 * @info: The parameters of the structs
 *
 * Return: THe read of the bytes
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t s, r, len;
	ssize_t q = 0;
	char **buf_m = &(info->arg), *m;

	_putchar(BUF_FLUSH);
	q = input_buf(info, &buf, &len);
	if (q == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		r = s; /* init new iterator to current buf position */
		m = buf + s; /* get pointer for return */

		check_chain(info, buf, &r, s, len);
		while (r < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &r))
				break;
			r++;
		}

		s = r + 1; /* increment past nulled ';'' */
		if (s >= len) /* reached end of buffer? */
		{
			s = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_m = m; /* pass back pointer to current command position */
		return (_strlen(m)); /* return length of current command */
	}
	*buf_m = buf; /* else not a chain, pass back buffer from _getline() */
	return (q); /* return length of buffer from _getline() */
}
/**
 * read_buf - The read of the buffer
 * @i: the size of the parameters
 * @info: The parametres of the struct
 * @buf: The buffer of the parameters
 * Return: q
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t q = 0;

	if (*i)
		return (0);
	q = read(info->readfd, buf, READ_BUF_SIZE);
	if (q >= 0)
		*i = q;
	return (q);
}
/**
 * _getline - gets the line os next input from STDIN
 * @ptr: the addresses of pointer to buffer preallocated or NULL
 * @info: The parameters of the struct
 * @length: THe size of preallocated ptr buffer or NULL
 * Return: q
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t s, len;
	size_t k;
	ssize_t q = 0, c = 0;
	char *m = NULL, *new_m = NULL, *l;

	m = *ptr;
	if (m && length)
		c = *length;
	if (s == len)
		s = len = 0;
	q = read_buf(info, buf, &len);
	if (q == -1 || (q == 0 && len == 0))
		return (-1);

	l = _strchr(buf + s, '\n');
	k = l ? 1 + (unsigned int)(l - buf) : len;
	new_m = _realloc(m, c, c ? c + k : k + 1);
	if (!new_m) /* MALLOC FAILURE! */
		return (m ? free(m), -1 : -1);

	if (c)
		_strncat(new_m, buf + s, k - s);
	else
		_strncpy(new_m, buf + s, k - s + 1);

	c += k - s;
	s = k;
	m = new_m;

	if (length)
		*length = c;
	*ptr = m;
	return (c);
}
/**
 * sigintHandler - The blocks of the ctrl-C
 * @sig_num: The signal of the numbers
 *
 * Return: The void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
