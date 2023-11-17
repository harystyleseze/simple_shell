#include "my_shell.h"

/**
 * func_clear_info - clear info_struct struct
 * @info_struct: address of struct
 */

void func_clear_info(info_t *info_struct)
{
	info_struct->arg = NULL;
	info_struct->argv = NULL;
	info_struct->file_path = NULL;
	info_struct->argc = 0;
}

/**
 * func_set_info - set struct
 * @info_struct: address of struct
 * @argv_count: vector of argument
 */
void func_set_info(info_t *info_struct, char **argv_count)
{
	int i = 0;

	info_struct->fname = argv_count[0];
	if (info_struct->arg)
	{
		info_struct->argv = strtow_func(info_struct->arg, " \t");
		if (!info_struct->argv)
		{
			info_struct->argv = malloc(sizeof(char *) * 2);
			if (info_struct->argv)
			{
				info_struct->argv[0] = func_strdup(info_struct->arg);
				info_struct->argv[1] = NULL;
			}
		}
		for (i = 0; info_struct->argv && info_struct->argv[i]; i++)
			;
		info_struct->argc = i;

		func_replace_alias(info_struct);
		func_replace_vars(info_struct);
	}
}

/**
 * func_free_info - release struct
 * @info_struct: address of struct
 * @all: free all
 * Return: true if successful
 */
void func_free_info(info_t *info_struct, int all)
{
	func_ffree(info_struct->argv);
	info_struct->argv = NULL;
	info_struct->file_path = NULL;
	if (all)
	{
		if (!info_struct->cmd_buf)
			free(info_struct->arg);
		if (info_struct->env)
			func_free_list(&(info_struct->env));
		if (info_struct->history)
			func_free_list(&(info_struct->history));
		if (info_struct->alias)
			func_free_list(&(info_struct->alias));
		func_ffree(info_struct->environ);
			info_struct->environ = NULL;
		func_bfree((void **)info_struct->cmd_buf);
		if (info_struct->readfd > 2)
			close(info_struct->readfd);
		func_putchar(BUF_FLUSH);
	}
}
