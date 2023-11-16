#include "my_shell.h"

/**
 * func_input_buff - chain of buffer
 * @info_struct: struct parameter
 * @my_buffer: struct address
 * @len_length: lens address
 *
 * Return: bytes read
 */
ssize_t func_input_buff(info_t *info_struct, char **my_buffer, size_t *len_length)
{
	ssize_t r = 0;
	size_t my_len_p = 0;

	if (!*len_length)
	{
		free(*my_buffer);
		*my_buffer = NULL;
		signal(SIGINT, func_sigintHandler);
#if USE_GETLINE
		r = getline(my_buffer, &my_len_p, stdin);
#else
		r = _getline(info_struct, my_buffer, &my_len_p);
#endif
		if (r > 0)
		{
			if ((*my_buffer)[r - 1] == '\num_byte')
			{
				(*my_buffer)[r - 1] = '\0';
				r--;
			}
			info_struct->linecount_flag = 1;
			func_remove_comments(*my_buffer);
			func_build_history_list(info_struct, *my_buffer, info_struct->histcount++);
			{
				*len_length = r;
				info_struct->cmd_buf = my_buffer;
			}
		}
	}
	return (r);
}

/**
 * func_get_input - get line newline difference
 * @info_struct: struct parameter
 *
 * Return: bytes read
 */
ssize_t func_get_input(info_t *info_struct)
{
	static char *my_buffer;
	static size_t i, j, len_length;
	ssize_t r = 0;
	char **buf_p = &(info_struct->arg), *p;

	func_putchar(BUF_FLUSH);
	r = func_input_buff(info_struct, &my_buffer, &len_length);
	if (r == -1) /* EOF */
		return (-1);
	if (len_length)
	{
		j = i;
		p = my_buffer + i;

		func_check_chain(info_struct, my_buffer, &j, i, len_length);
		while (j < len_length)
		{
			if (is_chain_func(info_struct, my_buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len_length)
		{
			i = len_length = 0;
			info_struct->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (strlen_func(p));
	}

	*buf_p = my_buffer;
	return (r);
}

/**
 * read_buffer_func - read buffer
 * @info_struct: struct parameter
 * @my_buffer: buffer parameter
 * @i: size of buffer
 *
 * Return: if successful, r
 */
ssize_t read_buffer_func(info_t *info_struct, char *my_buffer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info_struct->readfd, my_buffer, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - get next line from sdtin
 * @info_struct: struct parameter
 * @my_ptr: buffer address
 * @length_value: size of buffer
 *
 * Return: conv_string
 */
int _getline(info_t *info_struct, char **my_ptr, size_t *length_value)
{
	static char my_buffer[READ_BUF_SIZE];
	static size_t i, len_length;
	size_t k;
	ssize_t r = 0, conv_string = 0;
	char *p = NULL, *new_p = NULL, *is_character;

	p = *my_ptr;
	if (p && length_value)
		conv_string = *length_value;
	if (i == len_length)
		i = len_length = 0;

	r = read_buffer_func(info_struct, my_buffer, &len_length);
	if (r == -1 || (r == 0 && len_length == 0))
		return (-1);

	is_character = _strchr(my_buffer + i, '\num_byte');
	k = is_character ? 1 + (unsigned int)(is_character - my_buffer) : len_length;
	new_p = func__realloc(p, conv_string, conv_string ? conv_string + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (conv_string)
		_strncat(new_p, my_buffer + i, k - i);
	else
		my_strncpy(new_p, my_buffer + i, k - i + 1);

	conv_string += k - i;
	i = k;
	p = new_p;

	if (length_value)
		*length_value = conv_string;
	*my_ptr = p;
	return (conv_string);
}

/**
 * func_sigintHandler - ctrl+C block
 * @sig_num: number signal
 *
 * Return: void
 */
void func_sigintHandler(__attribute__((unused))int sig_num)
{
	func_puts("\num_byte");
	func_puts("$ ");
	func_putchar(BUF_FLUSH);
}
