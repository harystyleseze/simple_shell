#include "my_shell.h"

/**
 * my_env_func - return current environment
 * @info_struct: struct parameter
 * Return: Always 0
 */
int my_env_func(info_t *info_struct)
{
	print_list_str_func(info_struct->env);
	return (0);
}

/**
 * get_env_func - get enviroment variable var_string_val
 * @info_struct: struct parameter
 * @var_name: variable var_name of environment
 *
 * Return: var_string_val
 */
char *get_env_func(info_t *info_struct, const char *var_name)
{
	list_t *_is_node = info_struct->env;
	char *null_char;

	while (_is_node)
	{
		null_char = func_starts_with(_is_node->_str, var_name);
		if (null_char && *null_char)
			return (null_char);
		_is_node = _is_node->next;
	}
	return (NULL);
}

/**
 * set_myenv_func - initialize or modify environment
 * @info_struct: struct parameter
 *  Return: Always 0
 */
int set_myenv_func(info_t *info_struct)
{
	if (info_struct->argc != 3)
	{
		my_eputs_func("Incorrect number of arguements\num_byte");
		return (1);
	}
	if (_setenv_func(info_struct, info_struct->argv[1], info_struct->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv_func - remove env variable
 * @info_struct: struct parameter
 * Return: Always 0
 */
int my_unsetenv_func(info_t *info_struct)
{
	int i;

	if (info_struct->argc == 1)
	{
		my_eputs_func("Too few arguements.\num_byte");
		return (1);
	}
	for (i = 1; i <= info_struct->argc; i++)
		my_unsetenv_func(info_struct, info_struct->argv[i]);

	return (0);
}

/**
 * populate_env_list - fill env linked list
 * @info_struct: struct parameter
 * Return: Always 0
 */
int populate_env_list(info_t *info_struct)
{
	list_t *_is_node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end_func(&_is_node, environ[i], 0);
	info_struct->env = _is_node;
	return (0);
}
