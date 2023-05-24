#include "shell.h"

/**
 * list_len - determineing the length of linked lists
 * @h: pointers to be first noded
 *
 * Return: size of the lists
 */
size_t list_len(const list_t *h)
{
	size_t u = 0;

	while (h)
	{
		h = h->next;
		u++;
	}
	return (u);
}

/**
 * list_to_strings - returned the array of strings of the list->str
 * @head: pointers to be first noded
 *
 * Return: arraies of the string
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t u = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !u)
		return (NULL);
	strs = malloc(sizeof(char *) * (u + 1));
	if (!strs)
		return (NULL);
	for (u = 0; node; node = node->next, u++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < u; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[u] = str;
	}
	strs[u] = NULL;
	return (strs);
}

/**
 * print_list - print all the elements of the list-t linked lists
 * @h: pointers to be the first noded
 *
 * Return: size of the list
 */
size_t print_list(const list_t *h)
{
	size_t u = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		u++;
	}
	return (u);
}

/**
 * node_starts_with - returns the node makes the string starts with prefix
 * @node: pointers to be listed the head
 * @prefix:math to string
 * @c: The next characters goes after prefixs to matchs
 *
 * Return:node match or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *v = NULL;

	while (node)
	{
		v = starts_with(node->str, prefix);
		if (v && ((c == -1) || (*v == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - geting the index of a node
 * @head: pointers to be listed the head
 * @node: pointers to be the node
 *
 * Return: node of index or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t u = 0;

	while (head)
	{
		if (head == node)
			return (u);
		head = head->next;
		u++;
	}
	return (-u);
}
