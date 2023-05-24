#include "shell.h"

/**
 * main - entry points
 * @ac: arg counts
 * @av: for  arg vectors
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int yd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (yd)
			: "r" (yd));

	if (ac == 2)
	{
		yd = open(av[1], O_RDONLY);
		if (yd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = yd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
