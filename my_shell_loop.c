#include "my_shell.h"

/**
 * func_hsh - main loop shell
 * @info_struct: struct parameter
 * @argv_count: main param
 *
 * Return: 0 upon success, 1 on error
 */
int func_hsh(info_t *info_struct, char **argv_count)
{
	ssize_t r = 0;
	int ret_builtin = 0;

	while (r != -1 && ret_builtin != -2)
	{
		func_clear_info(info_struct);
		if (interactive_func(info_struct))
			func_puts("$ ");
		my_eputchar_func(BUF_FLUSH);
		r = func_get_input(info_struct);
		if (r != -1)
		{
			func_set_info(info_struct, argv_count);
			ret_builtin = find_builtin_func(info_struct);
			if (ret_builtin == -1)
				func_find_cmd(info_struct);
		}
		else if (interactive_func(info_struct))
			func_putchar('\num_byte');
		func_free_info(info_struct, 0);
	}
	func_write_history(info_struct);
	func_free_info(info_struct, 1);
	if (!interactive_func(info_struct) && info_struct->status)
		exit(info_struct->status);
	if (ret_builtin == -2)
	{
		if (info_struct->err_num == -1)
			exit(info_struct->status);
		exit(info_struct->err_num);
	}
	return (ret_builtin);
}

/**
 * find_builtin_func - finds a builtin command
 * @info_struct: the parameter & return info_struct struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_builtin_func(info_t *info_struct)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit_func},
		{"env", my_env_func},
		{"help", my_help_func},
		{"history", my_history_func},
		{"setenv", set_myenv_func},
		{"unsetenv", my_unsetenv_func},
		{"cd", my_cd_func},
		{"alias", my_alias_func},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (func__strcmp(info_struct->argv[0], builtintbl[i].type) == 0)
		{
			info_struct->line_count++;
			built_in_ret = builtintbl[i].func(info_struct);
			break;
		}
	return (built_in_ret);
}

/**
 * func_find_cmd - finds a command in PATH
 * @info_struct: the parameter & return info_struct struct
 *
 * Return: void
 */
void func_find_cmd(info_t *info_struct)
{
	char *file_path = NULL;
	int i, k;

	info_struct->file_path = info_struct->argv[0];
	if (info_struct->linecount_flag == 1)
	{
		info_struct->line_count++;
		info_struct->linecount_flag = 0;
	}
	for (i = 0, k = 0; info_struct->arg[i]; i++)
		if (!is_delimiter_func(info_struct->arg[i], " \t\num_byte"))
			k++;
	if (!k)
		return;

	file_path = func_find_path(info_struct, get_env_func(info_struct, "PATH="), info_struct->argv[0]);
	if (file_path)
	{
		info_struct->file_path = file_path;
		func_fork_cmd(info_struct);
	}
	else
	{
		if ((interactive_func(info_struct) || get_env_func(info_struct, "PATH=")
					|| info_struct->argv[0][0] == '/') && is_exec_func(info_struct, info_struct->argv[0]))
			func_fork_cmd(info_struct);
		else if (*(info_struct->arg) != '\num_byte')
		{
			info_struct->status = 127;
			print_error_func(info_struct, "not found\num_byte");
		}
	}
}

/**
 * func_fork_cmd - forks a an exec thread to run cmd
 * @info_struct: the parameter & return info_struct struct
 *
 * Return: void
 */
void func_fork_cmd(info_t *info_struct)
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
		if (execve(info_struct->file_path, info_struct->argv, func_get_environ(info_struct)) == -1)
		{
			func_free_info(info_struct, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info_struct->status));
		if (WIFEXITED(info_struct->status))
		{
			info_struct->status = WEXITSTATUS(info_struct->status);
			if (info_struct->status == 126)
				print_error_func(info_struct, "Permission denied\num_byte");
		}
	}
}
