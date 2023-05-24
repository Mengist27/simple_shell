#include "shell.h"

/**
 * is_chain - Test when currenting the char in the buffer was a chain delimeter
 * @info: The parameters of struct
 * @buf: The char buffers
 * @p: address of the current position in buffer
 *
 * Return: 1 when chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t g = *p;

	if (buf[g] == '|' && buf[g + 1] == '|')
	{
		buf[g] = 0;
		g++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[g] == '&' && buf[g + 1] == '&')
	{
		buf[g] = 0;
		g++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[g] == ';') /* found end of this command */
	{
		buf[g] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = g;
	return (1);
}

/**
 * check_chain -we Checks should be continue chaining based on last status
 * @info: The parameters of the struct
 * @buf: The char buffers
 * @p: Address of the current position in the buffer
 * @i: starting of position in the buffer
 * @len: length of buffer
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t g = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			g = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			g = len;
		}
	}

	*p = g;
}

/**
 * replace_alias - Replacing an aliases in the tokenized strings
 * @info: The parameter struct
 *
 * Return: 1 When replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int u;
	list_t *node;
	char *p;

	for (u = 0; u < 10; u++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaceing a vars in the tokenized of the string
 * @info: The parameter struct
 *
 * Return: 1 when replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int u = 0;
	list_t *node;

	for (u = 0; info->argv[u]; u++)
	{
		if (info->argv[u][0] != '$' || !info->argv[u][1])
			continue;

		if (!_strcmp(info->argv[u], "$?"))
		{
			replace_string(&(info->argv[u]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[u], "$$"))
		{
			replace_string(&(info->argv[u]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[u][1], '=');
		if (node)
		{
			replace_string(&(info->argv[u]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[u], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Replaceing the string
 * @old: Address of old string
 * @new: New string
 *
 * Return: 1 when replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
