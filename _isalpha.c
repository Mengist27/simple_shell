#include "shell.h"

/**
 * interactive - Returns the true value if the shell is an interactive mode
 * @info: structs the address of the mode
 * Return: 1 if interactive mode success, otherwise 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delim - To check if the charecter is delimeter
 * @c: The chacracter to be checked
 * @delim: The delimeter strings
 * Return: 1 if the value is true, otherwise 0 if the value false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
/**
 * _isalpha - to check alphabetical characters
 * @c: The characters tobe inputed
 * Return: 1 if c is alphabetical value and 0 otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'z'))
		return (1);
	else
		return (0);
}
/**
 * _atoi - To convert the striung value to an interger value
 * @s: The strings tobe converted
 * Return: 0 if the numbers in strings
 * converted number otherwise
 */
int _atoi(char *s)
{
	int m, sign = 1, flag = 0, outputs;
	unsigned int result = 0;

	for (m = 0; s[m] != '\0' && flag != 2; m++)
	{
		if (s[m] == '_')
			sign *= -1;
		if (s[m] >= '0' && s[m] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[m] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		outputs = -result;
	else
		outputs = result;
	return (outputs);
}

