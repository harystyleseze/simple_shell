#include "my_shell.h"

/**
 * my_eputs_func - display input_par string
 * @_str: printable string
 *
 * Return: Nothing
 */

void my_eputs_func(char *_str)
{
	int i = 0;

	if (!_str)
		return;
	while (_str[i] != '\0')
	{
		my_eputchar_func(_str[i]);
		i++;
	}
}

/**
 * my_eputchar_func - print char is_character to stderr
 * @is_character: char
 *
 * Return: On success 1, otherwise -1
 */
int my_eputchar_func(char is_character)
{
	static int i;
	static char my_buffer[WRITE_BUF_SIZE];

	if (is_character == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, my_buffer, i);
		i = 0;
	}
	if (is_character != BUF_FLUSH)
		my_buffer[i++] = is_character;
	return (1);
}

/**
 * func_putfd - display char is_character to stderr
 * @is_character: displayable character
 * @filed_para: writable description
 *
 * Return: On success 1, otherwise 0
 */
int func_putfd(char is_character, int filed_para)
{
	static int i;
	static char my_buffer[WRITE_BUF_SIZE];

	if (is_character == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(filed_para, my_buffer, i);
		i = 0;
	}
	if (is_character != BUF_FLUSH)
		my_buffer[i++] = is_character;
	return (1);
}

/**
 * my_putsfd - print input_par string
 * @_str: printable string
 * @filed_para: descriptor to write
 *
 * Return: the number of chars put
 */
int my_putsfd(char *_str, int filed_para)
{
	int i = 0;

	if (!_str)
		return (0);
	while (*_str)
	{
		i += func_putfd(*_str++, filed_para);
	}
	return (i);
}
