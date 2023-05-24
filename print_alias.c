#include "shell.h"
/**
 * _myhistory - Displays the history list with one command line
 * @info: Structure containing arguments to maintain prototype func.
 *
 * Return: 0
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}
/**
 * unset_alias - To sets alias to strings
 * @info: Parametrs structs
 * @str: Parametr of string
 *
 * Return: 0
 */
int unset_alias(info_t *info, char *str)
{
	char *m, l;
	int det;

	m = _strchr(str, '=');
	if (!m)
		return (1);
	l = *m;
	*m = 0;
	det = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*m = l;
	return (det);
}
/**
 * print_alias - To prints an alias strings
 * @node: nodes of an alias
 *
 * Return: for success 0 and for error 1
 */
int print_alias(list_t *node)
{
	char *m = NULL, *a = NULL;

	if (node)
	{
		m = _strchr(node->str, '=');
		for (a = node->str; a <= m; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(m + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * set_alias - To sets alias to the strings
 * @info: Parameters structs
 * @str: The strings of the alias
 *
 * Return: 0 on success , 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *m;

	m = _strchr(str, '=');
	if (!m)
		return (1);
	if (!*++m)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * _myalias - mimics the alias builtin the man alias
 * @info: structure containing arguments to maintain prototpye func.
 *
 * Return: 0
 */
int _myalias(info_t *info)
{
	int s = 0;
	char *m = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;

		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (s = 1; info->argv[s]; s++)
	{
		m = _strchr(info->argv[s], '=');
		if (m)
			set_alias(info, info->argv[s]);
		else
			print_alias(node_starts_with(info->alias, info->argv[s], '='));
	}
	return (0);
}
