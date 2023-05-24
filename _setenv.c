#include "shell.h"
#include <stdio.h>

/**
 * get_environ - Returns the string array copy of our environ
 * @info: Structure containing arguments to maintain prototype func
 *
 * Return: 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}
/**
 * _unsetenv - To remove an enviroment variable
 * @info: Structure containing arguments to maintain prototype func
 * @var: The string of an env variable property
 *
 * Return: 1 on delete, otherwise 0
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t s = 0;
	char *m;

	if (!node || !var)
		return (0);

	while (node)
	{
		m = starts_with(node->str, var);
		if (m && *m == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), s);
			s = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		s++;
	}
	return (info->env_changed);
}
/**
 * _setenv - To initialize a new enviroment variable
 * @var: The string of an env variable property
 * @info: Structure containing arguments to maintain prototype func
 * @value: The strings of an env variable value
 *
 * Return: 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *m;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		m = starts_with(node->str, var);
		if (m && *m == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

