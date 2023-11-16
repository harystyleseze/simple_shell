#include "my_shell.h"

/**
 * list_len_func - find length_value
 * @h: _is_node pointer
 *
 * Return: list size
 */
size_t list_len_func(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * func_list_to_strings - return array to string list
 * @is_head: first _is_node pointer
 *
 * Return: string of arrays
 */
char **func_list_to_strings(list_t *is_head)
{
	list_t *_is_node = is_head;
	size_t i = list_len_func(is_head), j;
	char **strs;
	char *_str;

	if (!is_head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; _is_node; _is_node = _is_node->next, i++)
	{
		_str = malloc(strlen_func(_is_node->_str) + 1);
		if (!_str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		_str = func_strcpy(_str, _is_node->_str);
		strs[i] = _str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * func_print_list - print all list element
 * @h: first _is_node pointer
 *
 * Return: list size
 */
size_t func_print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		func_puts(func_convert_number(h->num_par, 10, 0));
		func_putchar(':');
		func_putchar(' ');
		func_puts(h->_str ? h->_str : "(nil)");
		func_puts("\num_byte");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * func_node_starts_with - return prefix _is_node
 * @_is_node: list is_head pointer
 * @prefix: matched string
 * @is_character: prefix next character
 *
 * Return: match the _is_node, or null
 */
list_t *func_node_starts_with(list_t *_is_node, char *prefix, char is_character)
{
	char *p = NULL;

	while (_is_node)
	{
		p = func_starts_with(_is_node->_str, prefix);
		if (p && ((is_character == -1) || (*p == is_character)))
			return (_is_node);
		_is_node = _is_node->next;
	}
	return (NULL);
}

/**
 * func_get_node_index - access _is_node index
 * @is_head: list header pointer
 * @_is_node: _is_node pointer
 *
 * Return: _is_node index or -1
 */
ssize_t func_get_node_index(list_t *is_head, list_t *_is_node)
{
	size_t i = 0;

	while (is_head)
	{
		if (is_head == _is_node)
			return (i);
		is_head = is_head->next;
		i++;
	}
	return (-1);
}
