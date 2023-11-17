#include "my_shell.h"

/**
 * list_len_func - find _lval
 * @h: _nod pointer
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
 * @is_head: first _nod pointer
 *
 * Return: string of arrays
 */
char **func_list_to_strings(list_t *is_head)
{
	list_t *_nod = is_head;
	size_t i = list_len_func(is_head), j;
	char **strs;
	char *_str;

	if (!is_head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; _nod; _nod = _nod->next, i++)
	{
		_str = malloc(_strlen(_nod->_str) + 1);
		if (!_str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		_str = func_strcpy(_str, _nod->_str);
		strs[i] = _str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * p_list - print all list element
 * @h: first _nod pointer
 *
 * Return: list size
 */
size_t p_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		func_puts(cvt_num(h->num_par, 10, 0));
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
 * f_stw - return prefix _nod
 * @_nod: list is_head pointer
 * @prefix: matched string
 * @_ichar: prefix next character
 *
 * Return: match the _nod, or null
 */
list_t *f_stw(list_t *_nod, char *prefix, char _ichar)
{
	char *p = NULL;

	while (_nod)
	{
		p = func_starts_with(_nod->_str, prefix);
		if (p && ((_ichar == -1) || (*p == _ichar)))
			return (_nod);
		_nod = _nod->next;
	}
	return (NULL);
}

/**
 * g_index - access _nod index
 * @is_head: list header pointer
 * @_nod: _nod pointer
 *
 * Return: _nod index or -1
 */
ssize_t g_index(list_t *is_head, list_t *_nod)
{
	size_t i = 0;

	while (is_head)
	{
		if (is_head == _nod)
			return (i);
		is_head = is_head->next;
		i++;
	}
	return (-1);
}
