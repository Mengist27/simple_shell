#include "shell.h"

/**
 * **strtow - split the string into the words. Repeating delimiters are ignored
 * @str: The input string
 * @d: The delimeters of the string
 * Return: The pointers to be an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int u, g, l, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (u = 0; str[u] != '\0'; u++)
		if (!is_delim(str[u], d) && (is_delim(str[u + 1], d) || !str[u + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (u = 0, g = 0; g < numwords; g++)
	{
		while (is_delim(str[u], d))
			u++;
		l = 0;
		while (!is_delim(str[u + l], d) && str[u + l])
			l++;
		s[g] = malloc((l + 1) * sizeof(char));
		if (!s[g])
		{
			for (l = 0; l < g; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < l; m++)
			s[g][m] = str[u++];
		s[g][m] = 0;
	}
	s[g] = NULL;
	return (s);
}

/**
 * **strtow2 - spliting the string of the into words
 * @str: The input string
 * @d: The delimeters
 * Return: the pointers to be an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int u, g, l, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (u = 0; str[u] != '\0'; u++)
		if ((str[u] != d && str[u + 1] == d) ||
				    (str[u] != d && !str[u + 1]) || str[u + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (u = 0, g = 0; g < numwords; g++)
	{
		while (str[u] == d && str[u] != d)
			u++;
		l = 0;
		while (str[u + l] != d && str[u + l] && str[u + l] != d)
			l++;
		s[g] = malloc((l + 1) * sizeof(char));
		if (!s[g])
		{
			for (l = 0; l < g; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < l; m++)
			s[g][m] = str[u++];
		s[g][m] = 0;
	}
	s[g] = NULL;
	return (s);
}
