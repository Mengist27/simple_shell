#include "shell.h"

/**
 * is_cmd - Determines when a files is an executables command
 * @info: The information struct
 * @path: path to be the files
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicated characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointers to be new buffers
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int u = 0, q = 0;

	for (q = 0, u = start; u < stop; u++)
		if (pathstr[u] != ':')
			buf[q++] = pathstr[u];
	buf[q] = 0;
	return (buf);
}

/**
 * find_path - Finds this cmd in to the PATH string
 * @info: The info struct
 * @pathstr: The PATH string
 * @cmd: the cmd to finding
 *
 * Return: fulling paths of cmd when found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int u = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[u] || pathstr[u] == ':')
		{
			path = dup_chars(pathstr, curr_pos, u);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[u])
				break;
			curr_pos = u;
		}
		u++;
	}
	return (NULL);
}

