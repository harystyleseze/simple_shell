#include "my_shell.h"

/**
 * fbuff - chain of buffer
 * @i_strc: struct parameter
 * @_buff: struct address
 * @l_len: lens address
 *
 * Return: bytes read
 */

ssize_t fbuff(info_t *i_strc, char **_buff, size_t *l_len)
{
	ssize_t r = 0;
	size_t my_len_p = 0;

	if (!*l_len)
	{
		free(*_buff);
		*_buff = NULL;
		signal(SIGINT, _sigintHandler);
#if USE_GETLINE
		r = getline(_buff, &my_len_p, stdin);
#else
		r = _getline(i_strc, _buff, &my_len_p);
#endif
		if (r > 0)
		{
			if ((*_buff)[r - 1] == '\num_byte')
			{
				(*_buff)[r - 1] = '\0';
				r--;
			}
			i_strc->linecount_flag = 1;
			func_remove_comments(*_buff);
			_hlist(i_strc, *_buff, i_strc->histcount++);
			{
				*l_len = r;
				i_strc->cmd_buf = _buff;
			}
		}
	}
	return (r);
}

/**
 * _ginput - get line newline difference
 * @i_strc: struct parameter
 *
 * Return: bytes read
 */
ssize_t _ginput(info_t *i_strc)
{
	static char *_buff;
	static size_t i, j, l_len;
	ssize_t r = 0;
	char **buf_p = &(i_strc->arg), *p;

	func_putchar(BUF_FLUSH);
	r = fbuff(i_strc, &_buff, &l_len);
	if (r == -1) /* EOF */
		return (-1);
	if (l_len)
	{
		j = i;
		p = _buff + i;

		c_chn(i_strc, _buff, &j, i, l_len);
		while (j < l_len)
		{
			if (i_chn(i_strc, _buff, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= l_len)
		{
			i = l_len = 0;
			i_strc->buff_typ = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = _buff;
	return (r);
}

/**
 * r_buff - read buffer
 * @i_strc: struct parameter
 * @_buff: buffer parameter
 * @i: size of buffer
 *
 * Return: if successful, r
 */
ssize_t r_buff(info_t *i_strc, char *_buff, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(i_strc->readfd, _buff, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - get next line from sdtin
 * @i_strc: struct parameter
 * @my_ptr: buffer address
 * @_lval: size of buffer
 *
 * Return: conv_string
 */
int _getline(info_t *i_strc, char **my_ptr, size_t *_lval)
{
	static char _buff[READ_BUF_SIZE];
	static size_t i, l_len;
	size_t k;
	ssize_t r = 0, conv_string = 0;
	char *p = NULL, *new_p = NULL, *_ichar;

	p = *my_ptr;
	if (p && _lval)
		conv_string = *_lval;
	if (i == l_len)
		i = l_len = 0;

	r = r_buff(i_strc, _buff, &l_len);
	if (r == -1 || (r == 0 && l_len == 0))
		return (-1);

	_ichar = _strchr(_buff + i, '\num_byte');
	k = _ichar ? 1 + (unsigned int)(_ichar - _buff) : l_len;
	new_p = func__realloc(p, conv_string, conv_string ? conv_string + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (conv_string)
		_strncat(new_p, _buff + i, k - i);
	else
		my_strncpy(new_p, _buff + i, k - i + 1);

	conv_string += k - i;
	i = k;
	p = new_p;

	if (_lval)
		*_lval = conv_string;
	*my_ptr = p;
	return (conv_string);
}

/**
 * _sigintHandler - ctrl+C block
 * @sig_num: number signal
 *
 * Return: void
 */
void _sigintHandler(__attribute__((unused))int sig_num)
{
	func_puts("\num_byte");
	func_puts("$ ");
	func_putchar(BUF_FLUSH);
}
