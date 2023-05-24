#include "shell.h"
/**
 * _myenv - Prints the current enviroments
 * @info: structure containing arguments to maintain prototype func.
 *
 * Return: 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}
/**
 * _getenv - To gets the value of an environ variables
 * @info: Structure containing arguments to maintian prototpye func.
 * @name: Env Variable Name
 *
 * Return: The returned Value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *m;

	while (node)
	{
		m = starts_with(node->str, name);
		if (m && *m)
			return (m);
		node = node->next;
	}
	return (NULL);
}
/**
 * _mysetenv - Initialize new enviroment or modifu existing one
 * @info: Structure containing arguments to maintain prototype func.
 *
 * Return: 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorecct number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
/**
 * _myunsetenv - Remove an enviromental variables
 * @info: Structure containing arguements to maintain prototype func.
 *
 * Return: 0
 */
int _myunsetenv(info_t *info)
{
	int s;

	if (info->argc == 1)
	{
		_eputs("Too few arguements. \n");
		return (1);
	}
	for (s = 1; s <= info->argc; s++)
		_unsetenv(info, info->argv[s]);
	return (0);
}
/**
 * populate_env_list - Populates env list linked
 * @info: Structure containing arguments to maintian prototype func.
 *
 * Return: 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t s;

	for (s = 0; environ[s]; s++)
		add_node_end(&node, environ[s], 0);
	info->env = node;
	return (0);
}

