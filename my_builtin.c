#include "my_shell.h"

/**
 * _histf - display history
 * @i_strc: argument struct
 *
 *  Return: 0 always
 */
int _histf(info_t *i_strc)
{
	p_list(i_strc->history);
	return (0);
}

/**
 * unset_al - to unset alias to string
 * @i_strc: struct parameter
 * @_str:  alias of the string
 *
 * Return: success 0,  error 1.
 */
int unset_al(info_t *i_strc, char *_str)
{
	char *null_char, conv_string;
	int _ret;

	null_char = _strchr(_str, '=');
	if (!null_char)
		return (1);
	conv_string = *null_char;
	*null_char = 0;
	_ret = del_index(&(i_strc->alias),
		g_index(i_strc->alias, f_stw(i_strc->alias, _str, -1)));
	*null_char = conv_string;
	return (_ret);
}

/**
 * set_ali - function to set alias to string
 * @i_strc: parameter struct
 * @_str: alias of string
 *
 * Return: on success 0, on error 1
 */
int set_ali(info_t *i_strc, char *_str)
{
	char *null_char;

	p = _strchr(_str, '=');
	if (!null_char)
		return (1);
	if (!*++null_char)
		return (unset_al(i_strc, _str));

	unset_al(i_strc, _str);
	return (add_node_end_func(&(i_strc->alias), _str, 0) == NULL);
}

/**
 * p_ali - print alias
 * @_nod: _nod of the alias
 *
 * Return: 0 upon success, otherwise 1
 */
int p_ali(list_t *_nod)
{
	char *null_char = NULL, *b = NULL;

	if (_nod)
	{
		null_char = _strchr(_nod->_str, '=');
		for (b = _nod->_str; b <= null_char; b++)
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
 * @i_strc: argument struct
 *  Return: Always 0
 */
int my_alias_func(info_t *i_strc)
{
	int i = 0;
	char *null_char = NULL;
	list_t *_nod = NULL;

	if (i_strc->argc == 1)
	{
		_nod = i_strc->alias;
		while (_nod)
		{
			p_ali(_nod);
			_nod = _nod->next;
		}
		return (0);
	}
	for (i = 1; i_strc->argv[i]; i++)
	{
		null_char = _strchr(i_strc->argv[i], '=');
		if (null_char)
			set_ali(i_strc, i_strc->argv[i]);
		else
			p_ali(f_stw(i_strc->alias, i_strc->argv[i], '='));
	}

	return (0);
}
