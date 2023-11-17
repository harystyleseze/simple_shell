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
 * my_eputchar_func - print char _ichar to stderr
 * @_ichar: char
 *
 * Return: On success 1, otherwise -1
 */
int my_eputchar_func(char _ichar)
{
	static int i;
	static char _buff[WRITE_BUF_SIZE];

	if (_ichar == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, _buff, i);
		i = 0;
	}
	if (_ichar != BUF_FLUSH)
		_buff[i++] = _ichar;
	return (1);
}

/**
 * func_putfd - display char _ichar to stderr
 * @_ichar: displayable character
 * @filed_para: writable description
 *
 * Return: On success 1, otherwise 0
 */
int func_putfd(char _ichar, int filed_para)
{
	static int i;
	static char _buff[WRITE_BUF_SIZE];

	if (_ichar == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(filed_para, _buff, i);
		i = 0;
	}
	if (_ichar != BUF_FLUSH)
		_buff[i++] = _ichar;
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
