#include "my_shell.h"

/**
 * func_get_environ - function to return string array
 * @info_struct: argument struct
 * Return: Always 0
 */
char **func_get_environ(info_t *info_struct)
{
	if (!info_struct->environ || info_struct->env_changed)
	{
		info_struct->environ = func_list_to_strings(info_struct->env);
		info_struct->env_changed = 0;
	}

	return (info_struct->environ);
}

/**
 * my_unsetenv_func - eliminate all env variable
 * @info_struct: argument struct
 *  Return: 1 on delete, 0 otherwise
 * @_varenv: string of env _varenv property
 */
int my_unsetenv_func(info_t *info_struct, char *_varenv)
{
	list_t *_is_node = info_struct->env;
	size_t i = 0;
	char *p;

	if (!_is_node || !_varenv)
		return (0);

	while (_is_node)
	{
		p = func_starts_with(_is_node->_str, _varenv);
		if (p && *p == '=')
		{
			info_struct->env_changed = func_delete_index_node(&(info_struct->env), i);
			i = 0;
			_is_node = info_struct->env;
			continue;
		}
		_is_node = _is_node->next;
		i++;
	}
	return (info_struct->env_changed);
}

/**
 * _setenv_func - initialize new env _varenv
 * @info_struct: argument struct
 * @_varenv: string env _varenv
 * @var_string_val: var_string_val of string env _varenv
 * Return: Always 0
 */
int _setenv_func(info_t *info_struct, char *_varenv, char *var_string_val)
{
	char *my_buffer = NULL;
	list_t *_is_node;
	char *p;

	if (!_varenv || !var_string_val)
		return (0);

	my_buffer = malloc(strlen_func(_varenv) + strlen_func(var_string_val) + 2);
	if (!my_buffer)
		return (1);
	func_strcpy(my_buffer, _varenv);
	func_strcat(my_buffer, "=");
	func_strcat(my_buffer, var_string_val);
	_is_node = info_struct->env;
	while (_is_node)
	{
		p = func_starts_with(_is_node->_str, _varenv);
		if (p && *p == '=')
		{
			free(_is_node->_str);
			_is_node->_str = my_buffer;
			info_struct->env_changed = 1;
			return (0);
		}
		_is_node = _is_node->next;
	}
	add_node_end_func(&(info_struct->env), my_buffer, 0);
	free(my_buffer);
	info_struct->env_changed = 1;
	return (0);
}
