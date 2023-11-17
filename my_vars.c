#include "my_shell.h"

/**
 * i_chn - test current char
 * @i_strc: the parameter struct
 * @_buff: the char buffer
 * @p: address of current position in _buff
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */

int i_chn(info_t *i_strc, char *_buff, size_t *p)
{
	size_t j = *p;

	if (_buff[j] == '|' && _buff[j + 1] == '|')
	{
		_buff[j] = 0;
		j++;
		i_strc->buff_typ = CMD_OR;
	}
	else if (_buff[j] == '&' && _buff[j + 1] == '&')
	{
		_buff[j] = 0;
		j++;
		i_strc->buff_typ = CMD_AND;
	}
	else if (_buff[j] == ';')
	{
		_buff[j] = 0;
		i_strc->buff_typ = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * c_chn - checks chaining based on last status
 * @i_strc: the parameter struct
 * @_buff: the char buffer
 * @p: address of current position in _buff
 * @i: starting position in _buff
 * @l_len: _lval of _buff
 *
 * Return: Void
 */
void c_chn(info_t *i_strc, char *_buff, size_t *p, size_t i, size_t l_len)
{
	size_t j = *p;

	if (i_strc->buff_typ == CMD_AND)
	{
		if (i_strc->status)
		{
			_buff[i] = 0;
			j = l_len;
		}
	}
	if (i_strc->buff_typ == CMD_OR)
	{
		if (!i_strc->status)
		{
			_buff[i] = 0;
			j = l_len;
		}
	}

	*p = j;
}

/**
 * rep_ali - replaces an aliases in the tokenized string
 * @i_strc: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_ali(info_t *i_strc)
{
	int i;
	list_t *_nod;
	char *p;

	for (i = 0; i < 10; i++)
	{
		_nod = f_stw(i_strc->alias, i_strc->argv[0], '=');
		if (!_nod)
			return (0);
		free(i_strc->argv[0]);
		p = _strchr(_nod->_str, '=');
		if (!p)
			return (0);
		p = func_strdup(p + 1);
		if (!p)
			return (0);
		i_strc->argv[0] = p;
	}
	return (1);
}

/**
 * rep_var - replaces vars in the tokenized string
 * @i_strc: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_var(info_t *i_strc)
{
	int i = 0;
	list_t *_nod;

	for (i = 0; i_strc->argv[i]; i++)
	{
		if (i_strc->argv[i][0] != '$' || !i_strc->argv[i][1])
			continue;

		if (!func__strcmp(i_strc->argv[i], "$?"))
		{
			rep_str(&(i_strc->argv[i]),
					func_strdup(cvt_num(i_strc->status, 10, 0)));
			continue;
		}
		if (!func__strcmp(i_strc->argv[i], "$$"))
		{
			rep_str(&(i_strc->argv[i]),
					func_strdup(cvt_num(getpid(), 10, 0)));
			continue;
		}
		_nod = f_stw(i_strc->env, &i_strc->argv[i][1], '=');
		if (_nod)
		{
			rep_str(&(i_strc->argv[i]),
					func_strdup(_strchr(_nod->_str, '=') + 1));
			continue;
		}
		rep_str(&i_strc->argv[i], func_strdup(""));

	}
	return (0);
}

/**
 * rep_str - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
