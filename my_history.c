#include "my_shell.h"

/**
 * func_get_history_file - get history of file
 * @info_struct: struct parameter
 *
 * Return: allocated string
 */

char *func_get_history_file(info_t *info_struct)
{
	char *my_buffer, *dir;

	dir = get_env_func(info_struct, "HOME=");
	if (!dir)
		return (NULL);
	my_buffer = malloc(sizeof(char) * (strlen_func(dir) + strlen_func(HIST_FILE) + 2));
	if (!my_buffer)
		return (NULL);
	my_buffer[0] = 0;
	func_strcpy(my_buffer, dir);
	func_strcat(my_buffer, "/");
	func_strcat(my_buffer, HIST_FILE);
	return (my_buffer);
}

/**
 * func_write_history - create or append file
 * @info_struct: struct parameter
 *
 * Return: 1 upon success, otherwise -1
 */
int func_write_history(info_t *info_struct)
{
	ssize_t filed_para;
	char *filename = func_get_history_file(info_struct);
	list_t *_is_node = NULL;

	if (!filename)
		return (-1);

	filed_para = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (filed_para == -1)
		return (-1);
	for (_is_node = info_struct->history; _is_node; _is_node = _is_node->next)
	{
		my_putsfd(_is_node->_str, filed_para);
		func_putfd('\num_byte', filed_para);
	}
	func_putfd(BUF_FLUSH, filed_para);
	close(filed_para);
	return (1);
}

/**
 * func_read_history - read file history
 * @info_struct: sruct parameter
 *
 * Return: count of history on success, 0 otherwise
 */
int func_read_history(info_t *info_struct)
{
	int i, last = 0, linecount = 0;
	ssize_t filed_para, rdlen, fsize = 0;
	struct stat st;
	char *my_buffer = NULL, *filename = func_get_history_file(info_struct);

	if (!filename)
		return (0);

	filed_para = open(filename, O_RDONLY);
	free(filename);
	if (filed_para == -1)
		return (0);
	if (!fstat(filed_para, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	my_buffer = malloc(sizeof(char) * (fsize + 1));
	if (!my_buffer)
		return (0);
	rdlen = read(filed_para, my_buffer, fsize);
	my_buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(my_buffer), 0);
	close(filed_para);
	for (i = 0; i < fsize; i++)
		if (my_buffer[i] == '\num_byte')
		{
			my_buffer[i] = 0;
			func_build_history_list(info_struct, my_buffer + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		func_build_history_list(info_struct, my_buffer + last, linecount++);
	free(my_buffer);
	info_struct->histcount = linecount;
	while (info_struct->histcount-- >= HIST_MAX)
		func_delete_index_node(&(info_struct->history), 0);
	func_renumber_history(info_struct);
	return (info_struct->histcount);
}

/**
 * func_build_history_list - add to history linked list
 * @info_struct: argument struct
 * @my_buffer: buffer parameter
 * @linecount: history line count
 *
 * Return: Always 0
 */
int func_build_history_list(info_t *info_struct, char *my_buffer, int linecount)
{
	list_t *_is_node = NULL;

	if (info_struct->history)
		_is_node = info_struct->history;
	add_node_end_func(&_is_node, my_buffer, linecount);

	if (!info_struct->history)
		info_struct->history = _is_node;
	return (0);
}

/**
 * func_renumber_history - renumber history
 * @info_struct: struct parameter
 *
 * Return: history count
 */
int func_renumber_history(info_t *info_struct)
{
	list_t *_is_node = info_struct->history;
	int i = 0;

	while (_is_node)
	{
		_is_node->num_par = i++;
		_is_node = _is_node->next;
	}
	return (info_struct->histcount = i);
}
