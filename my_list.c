#include "my_shell.h"

/**
 * add_node_func - add _is_node to list
 * @node_head: address of _is_node
 * @_str: _is_node _str
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
 * add_node_end_func - add _is_node to end of list
 * @node_head: pointer to _is_node
 * @_str: _is_node _str
 * @num_par: _is_node index history
 *
 * Return: list size
 */
list_t *add_node_end_func(list_t **node_head, const char *_str, int num_par)
{
	list_t *new_node, *_is_node;

	if (!node_head)
		return (NULL);

	_is_node = *node_head;
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
	if (_is_node)
	{
		while (_is_node->next)
			_is_node = _is_node->next;
		_is_node->next = new_node;
	}
	else
		*node_head = new_node;
	return (new_node);
}

/**
 * print_list_str_func - print _str element
 * @h: first _is_node pointer
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
 * func_delete_index_node - delete _is_node
 * @node_head: pointer to _is_node
 * @index: deleted index
 *
 * Return: 1 upon success, otheriwse 0 on failure
 */
int func_delete_index_node(list_t **node_head, unsigned int index)
{
	list_t *_is_node, *prev_node;
	unsigned int i = 0;

	if (!node_head || !*node_head)
		return (0);

	if (!index)
	{
		_is_node = *node_head;
		*node_head = (*node_head)->next;
		free(_is_node->_str);
		free(_is_node);
		return (1);
	}
	_is_node = *node_head;
	while (_is_node)
	{
		if (i == index)
		{
			prev_node->next = _is_node->next;
			free(_is_node->_str);
			free(_is_node);
			return (1);
		}
		i++;
		prev_node = _is_node;
		_is_node = _is_node->next;
	}
	return (0);
}

/**
 * func_free_list - release all nodes
 * @head_ptr: pointer to _is_node
 *
 * Return: void
 */
void func_free_list(list_t **head_ptr)
{
	list_t *_is_node, *next_node, *node_head;

	if (!head_ptr || !*head_ptr)
		return;
	node_head = *head_ptr;
	_is_node = node_head;
	while (_is_node)
	{
		next_node = _is_node->next;
		free(_is_node->_str);
		free(_is_node);
		_is_node = next_node;
	}
	*head_ptr = NULL;
}
