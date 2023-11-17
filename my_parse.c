#include "my_shell.h"

/**
 * i_exec - check executable
 * @i_strc: struct parameter
 * @file_path: file file_path
 *
 * Return: 1 if successful, 0 otherwise
 */
int i_exec(info_t *i_strc, char *file_path)
{
	struct stat st;

	(void)i_strc;
	if (!file_path || stat(file_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * func_dup_chars - check duplicate
 * @path_str: string file_path
 * @start: start file_path
 * @stop: end index
 *
 * Return: new buffer pointer
 */
char *func_dup_chars(char *path_str, int start, int stop)
{
	static char _buff[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (path_str[i] != ':')
			_buff[k++] = path_str[i];
	_buff[k] = 0;
	return (_buff);
}

/**
 * f_path - file_path string finder
 * @i_strc: struct i_strc
 * @path_str: string file_path
 * @cmd: find cmd
 *
 * Return: full file_path, or null
 */
char *f_path(info_t *i_strc, char *path_str, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *file_path;

	if (!path_str)
		return (NULL);
	if ((_strlen(cmd) > 2) && func_starts_with(cmd, "./"))
	{
		if (i_exec(i_strc, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			file_path = func_dup_chars(path_str, curr_pos, i);
			if (!*file_path)
				func_strcat(file_path, cmd);
			else
			{
				func_strcat(file_path, "/");
				func_strcat(file_path, cmd);
			}
			if (i_exec(i_strc, file_path))
				return (file_path);
			if (!path_str[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
