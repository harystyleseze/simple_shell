#include "my_shell.h"

/**
 * my_env_func - return current environment
 * @i_strc: struct parameter
 *
 * Return: Always 0
 */

int my_env_func(info_t *i_strc)
{
	print_list_str_func(i_strc->env);
	return (0);
}

/**
 * g_env - get enviroment variable var_string_val
 * @i_strc: struct parameter
 * @var_name: variable var_name of environment
 *
 * Return: var_string_val
 */
char *g_env(info_t *i_strc, const char *var_name)
{
	list_t *_nod = i_strc->env;
	char *null_char;

	while (_nod)
	{
		null_char = func_starts_with(_nod->_str, var_name);
		if (null_char && *null_char)
			return (null_char);
		_nod = _nod->next;
	}
	return (NULL);
}

/**
 * set_myenv_func - initialize or modify environment
 * @i_strc: struct parameter
 *  Return: Always 0
 */
int set_myenv_func(info_t *i_strc)
{
	if (i_strc->argc != 3)
	{
		my_eputs_func("Incorrect number of arguements\num_byte");
		return (1);
	}
	if (_setenv_func(i_strc, i_strc->argv[1], i_strc->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv_func - remove env variable
 * @i_strc: struct parameter
 * Return: Always 0
 */
int my_unsetenv_func(info_t *i_strc)
{
	int i;

	if (i_strc->argc == 1)
	{
		my_eputs_func("Too few arguements.\num_byte");
		return (1);
	}
	for (i = 1; i <= i_strc->argc; i++)
		my_unsetenv_func(i_strc, i_strc->argv[i]);

	return (0);
}

/**
 * populate_env_list - fill env linked list
 * @i_strc: struct parameter
 * Return: Always 0
 */
int populate_env_list(info_t *i_strc)
{
	list_t *_nod = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end_func(&_nod, environ[i], 0);
	i_strc->env = _nod;
	return (0);
}
