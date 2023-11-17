#include "my_shell.h"

/**
 * get_env - function to return string array
 * @i_strc: argument struct
 * Return: Always 0
 */

char **get_env(info_t *i_strc)
{
	if (!i_strc->environ || i_strc->env_changed)
	{
		i_strc->environ = func_list_to_strings(i_strc->env);
		i_strc->env_changed = 0;
	}

	return (i_strc->environ);
}

/**
 * my_unsetenv_func - eliminate all env variable
 * @i_strc: argument struct
 *  Return: 1 on delete, 0 otherwise
 * @_varenv: string of env _varenv property
 */
int my_unsetenv_func(info_t *i_strc, char *_varenv)
{
	list_t *_nod = i_strc->env;
	size_t i = 0;
	char *p;

	if (!_nod || !_varenv)
		return (0);

	while (_nod)
	{
		p = func_starts_with(_nod->_str, _varenv);
		if (p && *p == '=')
		{
			i_strc->env_changed = del_index(&(i_strc->env), i);
			i = 0;
			_nod = i_strc->env;
			continue;
		}
		_nod = _nod->next;
		i++;
	}
	return (i_strc->env_changed);
}

/**
 * _setenv_func - initialize new env _varenv
 * @i_strc: argument struct
 * @_varenv: string env _varenv
 * @var_string_val: var_string_val of string env _varenv
 * Return: Always 0
 */
int _setenv_func(info_t *i_strc, char *_varenv, char *var_string_val)
{
	char *_buff = NULL;
	list_t *_nod;
	char *p;

	if (!_varenv || !var_string_val)
		return (0);

	_buff = malloc(_strlen(_varenv) + _strlen(var_string_val) + 2);
	if (!_buff)
		return (1);
	func_strcpy(_buff, _varenv);
	func_strcat(_buff, "=");
	func_strcat(_buff, var_string_val);
	_nod = i_strc->env;
	while (_nod)
	{
		p = func_starts_with(_nod->_str, _varenv);
		if (p && *p == '=')
		{
			free(_nod->_str);
			_nod->_str = _buff;
			i_strc->env_changed = 1;
			return (0);
		}
		_nod = _nod->next;
	}
	add_node_end_func(&(i_strc->env), _buff, 0);
	free(_buff);
	i_strc->env_changed = 1;
	return (0);
}
