#include "my_shell.h"

/**
 * is_chain_func - test current char
 * @info_struct: the parameter struct
 * @my_buffer: the char buffer
 * @p: address of current position in my_buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain_func(info_t *info_struct, char *my_buffer, size_t *p)
{
	size_t j = *p;

	if (my_buffer[j] == '|' && my_buffer[j + 1] == '|')
	{
		my_buffer[j] = 0;
		j++;
		info_struct->cmd_buf_type = CMD_OR;
	}
	else if (my_buffer[j] == '&' && my_buffer[j + 1] == '&')
	{
		my_buffer[j] = 0;
		j++;
		info_struct->cmd_buf_type = CMD_AND;
	}
	else if (my_buffer[j] == ';')
	{
		my_buffer[j] = 0;
		info_struct->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * func_check_chain - checks chaining based on last status
 * @info_struct: the parameter struct
 * @my_buffer: the char buffer
 * @p: address of current position in my_buffer
 * @i: starting position in my_buffer
 * @len_length: length_value of my_buffer
 *
 * Return: Void
 */
void func_check_chain(info_t *info_struct, char *my_buffer, size_t *p, size_t i, size_t len_length)
{
	size_t j = *p;

	if (info_struct->cmd_buf_type == CMD_AND)
	{
		if (info_struct->status)
		{
			my_buffer[i] = 0;
			j = len_length;
		}
	}
	if (info_struct->cmd_buf_type == CMD_OR)
	{
		if (!info_struct->status)
		{
			my_buffer[i] = 0;
			j = len_length;
		}
	}

	*p = j;
}

/**
 * func_replace_alias - replaces an aliases in the tokenized string
 * @info_struct: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int func_replace_alias(info_t *info_struct)
{
	int i;
	list_t *_is_node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		_is_node = func_node_starts_with(info_struct->alias, info_struct->argv[0], '=');
		if (!_is_node)
			return (0);
		free(info_struct->argv[0]);
		p = _strchr(_is_node->_str, '=');
		if (!p)
			return (0);
		p = func_strdup(p + 1);
		if (!p)
			return (0);
		info_struct->argv[0] = p;
	}
	return (1);
}

/**
 * func_replace_vars - replaces vars in the tokenized string
 * @info_struct: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int func_replace_vars(info_t *info_struct)
{
	int i = 0;
	list_t *_is_node;

	for (i = 0; info_struct->argv[i]; i++)
	{
		if (info_struct->argv[i][0] != '$' || !info_struct->argv[i][1])
			continue;

		if (!func__strcmp(info_struct->argv[i], "$?"))
		{
			replace_string_func(&(info_struct->argv[i]),
					func_strdup(func_convert_number(info_struct->status, 10, 0)));
			continue;
		}
		if (!func__strcmp(info_struct->argv[i], "$$"))
		{
			replace_string_func(&(info_struct->argv[i]),
					func_strdup(func_convert_number(getpid(), 10, 0)));
			continue;
		}
		_is_node = func_node_starts_with(info_struct->env, &info_struct->argv[i][1], '=');
		if (_is_node)
		{
			replace_string_func(&(info_struct->argv[i]),
					func_strdup(_strchr(_is_node->_str, '=') + 1));
			continue;
		}
		replace_string_func(&info_struct->argv[i], func_strdup(""));

	}
	return (0);
}

/**
 * replace_string_func - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string_func(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
