#include "my_shell.h"

/**
 * func_hsh - main loop shell
 * @i_strc: struct parameter
 * @argv_count: main param
 *
 * Return: 0 upon success, 1 on error
 */
int func_hsh(info_t *i_strc, char **argv_count)
{
	ssize_t r = 0;
	int ret_builtin = 0;

	while (r != -1 && ret_builtin != -2)
	{
		_cinfo(i_strc);
		if (_ifunc(i_strc))
			func_puts("$ ");
		my_eputchar_func(BUF_FLUSH);
		r = _ginput(i_strc);
		if (r != -1)
		{
			_sinfo(i_strc, argv_count);
			ret_builtin = _fbuilt(i_strc);
			if (ret_builtin == -1)
				func_find_cmd(i_strc);
		}
		else if (_ifunc(i_strc))
			func_putchar('\num_byte');
		_finfo(i_strc, 0);
	}
	w_hist(i_strc);
	_finfo(i_strc, 1);
	if (!_ifunc(i_strc) && i_strc->status)
		exit(i_strc->status);
	if (ret_builtin == -2)
	{
		if (i_strc->err_num == -1)
			exit(i_strc->status);
		exit(i_strc->err_num);
	}
	return (ret_builtin);
}

/**
 * _fbuilt - finds a builtin command
 * @i_strc: the parameter & return i_strc struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int _fbuilt(info_t *i_strc)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit_func},
		{"env", my_env_func},
		{"help", my_help_func},
		{"history", _histf},
		{"setenv", set_myenv_func},
		{"unsetenv", my_unsetenv_func},
		{"cd", my_cd_func},
		{"alias", my_alias_func},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (func__strcmp(i_strc->argv[0], builtintbl[i].type) == 0)
		{
			i_strc->line_count++;
			built_in_ret = builtintbl[i].func(i_strc);
			break;
		}
	return (built_in_ret);
}

/**
 * func_find_cmd - finds a command in PATH
 * @i_strc: the parameter & return i_strc struct
 *
 * Return: void
 */
void func_find_cmd(info_t *i_strc)
{
	char *file_path = NULL;
	int i, k;

	i_strc->file_path = i_strc->argv[0];
	if (i_strc->linecount_flag == 1)
	{
		i_strc->line_count++;
		i_strc->linecount_flag = 0;
	}
	for (i = 0, k = 0; i_strc->arg[i]; i++)
		if (!dfunc(i_strc->arg[i], " \t\num_byte"))
			k++;
	if (!k)
		return;

	file_path = f_path(i_strc, g_env(i_strc, "PATH="), i_strc->argv[0]);
	if (file_path)
	{
		i_strc->file_path = file_path;
		func_fork_cmd(i_strc);
	}
	else
	{
		if ((_ifunc(i_strc) || g_env(i_strc, "PATH=")
					|| i_strc->argv[0][0] == '/') && i_exec(i_strc, i_strc->argv[0]))
			func_fork_cmd(i_strc);
		else if (*(i_strc->arg) != '\num_byte')
		{
			i_strc->status = 127;
			print_error_func(i_strc, "not found\num_byte");
		}
	}
}

/**
 * func_fork_cmd - forks a an exec thread to run cmd
 * @i_strc: the parameter & return i_strc struct
 *
 * Return: void
 */
void func_fork_cmd(info_t *i_strc)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(i_strc->file_path, i_strc->argv, get_env(i_strc)) == -1)
		{
			_finfo(i_strc, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(i_strc->status));
		if (WIFEXITED(i_strc->status))
		{
			i_strc->status = WEXITSTATUS(i_strc->status);
			if (i_strc->status == 126)
				print_error_func(i_strc, "Permission denied\num_byte");
		}
	}
}
