#include "my_shell.h"

/**
 * _cinfo - clear i_strc struct
 * @i_strc: address of struct
 */

void _cinfo(info_t *i_strc)
{
	i_strc->arg = NULL;
	i_strc->argv = NULL;
	i_strc->file_path = NULL;
	i_strc->argc = 0;
}

/**
 * _sinfo - set struct
 * @i_strc: address of struct
 * @argv_count: vector of argument
 */
void _sinfo(info_t *i_strc, char **argv_count)
{
	int i = 0;

	i_strc->fname = argv_count[0];
	if (i_strc->arg)
	{
		i_strc->argv = strtow_func(i_strc->arg, " \t");
		if (!i_strc->argv)
		{
			i_strc->argv = malloc(sizeof(char *) * 2);
			if (i_strc->argv)
			{
				i_strc->argv[0] = func_strdup(i_strc->arg);
				i_strc->argv[1] = NULL;
			}
		}
		for (i = 0; i_strc->argv && i_strc->argv[i]; i++)
			;
		i_strc->argc = i;

		rep_ali(i_strc);
		rep_var(i_strc);
	}
}

/**
 * _finfo - release struct
 * @i_strc: address of struct
 * @all: free all
 * Return: true if successful
 */
void _finfo(info_t *i_strc, int all)
{
	func_ffree(i_strc->argv);
	i_strc->argv = NULL;
	i_strc->file_path = NULL;
	if (all)
	{
		if (!i_strc->cmd_buf)
			free(i_strc->arg);
		if (i_strc->env)
			func_free_list(&(i_strc->env));
		if (i_strc->history)
			func_free_list(&(i_strc->history));
		if (i_strc->alias)
			func_free_list(&(i_strc->alias));
		func_ffree(i_strc->environ);
			i_strc->environ = NULL;
		func_bfree((void **)i_strc->cmd_buf);
		if (i_strc->readfd > 2)
			close(i_strc->readfd);
		func_putchar(BUF_FLUSH);
	}
}
