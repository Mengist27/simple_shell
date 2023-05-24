#include "shell.h"
#include <unistd.h>

/**
 * _myexit - to exits the shell
 * @info: the structure containing the arguments to maintain prototpye func
 * Return: 0 if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* if there an arguments */
	{
		exitcheck = _erratoi(info->argv[1]);

		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * _mycd - Changes the process of the current directory
 * @info: the structure containing the arguments to maintain prototpye func
 * Return: 0
 */
int _mycd(info_t *info)
{
	char *m, *dir, buffer[1024];
	int chdir_ret;

	m = getcwd(buffer, 1024);

	if (!m)
		_puts("TODO: >>getcwd failure mesege here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: What should this to be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "_") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(m);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: What should this to be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	} return (0);
}
/**
 * _myhelp - changes the process of the current directory
 * @info: structure containing arguments to maintain prototype func
 * Return: 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Help call works, function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused work arround */
	return (0);
}

