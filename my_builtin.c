#include "my_shell.h"

/**
 * my_history_func - display history
 * @info_struct: argument struct
 *
 *  Return: 0 always
 */
int my_history_func(info_t *info_struct)
{
	func_print_list(info_struct->history);
	return (0);
}

/**
 * my_unset_alias_func - to unset alias to string
 * @info_struct: struct parameter
 * @_str:  alias of the string
 *
 * Return: success 0,  error 1.
 */
int my_unset_alias_func(info_t *info_struct, char *_str)
{
	char *null_char, conv_string;
	int _ret;

	null_char = _strchr(_str, '=');
	if (!null_char)
		return (1);
	conv_string= *null_char;
	* null_char= 0;
	_ret = func_delete_index_node(&(info_struct->alias),
		func_get_node_index(info_struct->alias, func_node_starts_with(info_struct->alias, _str, -1)));
	*null_char = conv_string;
	return (_ret);
}

/**
 * set_alias_func - function to set alias to string
 * @info_struct: parameter struct
 * @_str: alias of string
 *
 * Return: on success 0, on error 1
 */
int set_alias_func(info_t *info_struct, char *_str)
{
	char *null_char;

	p = _strchr(_str, '=');
	if (!null_char)
		return (1);
	if (!*++null_char)
		return (my_unset_alias_func(info_struct, _str));

	my_unset_alias_func(info_struct, _str);
	return (add_node_end_func(&(info_struct->alias), _str, 0) == NULL);
}

/**
 * _print_alias_func - print alias
 * @_is_node: _is_node of the alias
 *
 * Return: 0 upon success, otherwise 1
 */
int _print_alias_func(list_t *_is_node)
{
	char *null_char = NULL, *b = NULL;

	if (_is_node)
	{
		null_char = _strchr(_is_node->_str, '=');
		for (b = _is_node->_str; b<= null_char; b++)
		func_putchar(*b);
		func_putchar('\'');
		func_puts(null_char + 1);
		func_puts("'\num_byte");
		return (0);
	}
	return (1);
}

/**
 * my_alias_func - to mimic man built-in alias
 * @info_struct: argument struct
 *  Return: Always 0
 */
int my_alias_func(info_t *info_struct)
{
	int i = 0;
	char *null_char = NULL;
	list_t *_is_node = NULL;

	if (info_struct->argc == 1)
	{
		_is_node = info_struct->alias;
		while (_is_node)
		{
			_print_alias_func(_is_node);
			_is_node = _is_node->next;
		}
		return (0);
	}
	for (i = 1; info_struct->argv[i]; i++)
	{
		null_char = _strchr(info_struct->argv[i], '=');
		if (null_char)
			set_alias_func(info_struct, info_struct->argv[i]);
		else
			_print_alias_func(func_node_starts_with(info_struct->alias, info_struct->argv[i], '='));
	}

	return (0);
}
