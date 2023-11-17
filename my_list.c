#include "my_shell.h"

/**
 * add_node_func - add _nod to list
 * @node_head: address of _nod
 * @_str: _nod _str
 * @num_par: index history
 *
 * Return: list size
 */

list_t *add_node_func(list_t **node_head, const char *_str, int num_par)
{
	list_t *new_head;

	if (!node_head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	func_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num_par = num_par;
	if (_str)
	{
		new_head->_str = func_strdup(_str);
		if (!new_head->_str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *node_head;
	*node_head = new_head;
	return (new_head);
}

/**
 * add_node_end_func - add _nod to end of list
 * @node_head: pointer to _nod
 * @_str: _nod _str
 * @num_par: _nod index history
 *
 * Return: list size
 */
list_t *add_node_end_func(list_t **node_head, const char *_str, int num_par)
{
	list_t *new_node, *_nod;

	if (!node_head)
		return (NULL);

	_nod = *node_head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	func_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num_par = num_par;
	if (_str)
	{
		new_node->_str = func_strdup(_str);
		if (!new_node->_str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (_nod)
	{
		while (_nod->next)
			_nod = _nod->next;
		_nod->next = new_node;
	}
	else
		*node_head = new_node;
	return (new_node);
}

/**
 * print_list_str_func - print _str element
 * @h: first _nod pointer
 *
 * Return: list size
 */
size_t print_list_str_func(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		func_puts(h->_str ? h->_str : "(nil)");
		func_puts("\num_byte");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * del_index - delete _nod
 * @node_head: pointer to _nod
 * @index: deleted index
 *
 * Return: 1 upon success, otheriwse 0 on failure
 */
int del_index(list_t **node_head, unsigned int index)
{
	list_t *_nod, *prev_node;
	unsigned int i = 0;

	if (!node_head || !*node_head)
		return (0);

	if (!index)
	{
		_nod = *node_head;
		*node_head = (*node_head)->next;
		free(_nod->_str);
		free(_nod);
		return (1);
	}
	_nod = *node_head;
	while (_nod)
	{
		if (i == index)
		{
			prev_node->next = _nod->next;
			free(_nod->_str);
			free(_nod);
			return (1);
		}
		i++;
		prev_node = _nod;
		_nod = _nod->next;
	}
	return (0);
}

/**
 * func_free_list - release all nodes
 * @head_ptr: pointer to _nod
 *
 * Return: void
 */
void func_free_list(list_t **head_ptr)
{
	list_t *_nod, *next_node, *node_head;

	if (!head_ptr || !*head_ptr)
		return;
	node_head = *head_ptr;
	_nod = node_head;
	while (_nod)
	{
		next_node = _nod->next;
		free(_nod->_str);
		free(_nod);
		_nod = next_node;
	}
	*head_ptr = NULL;
}
