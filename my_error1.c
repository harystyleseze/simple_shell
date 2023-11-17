#include "my_shell.h"

/**
 * my_erratoi_func - converts a string to an integer
 * @conv_string: convertible string
 * Return: 0 if non-string, otherwise, -1
 */

int my_erratoi_func(char *conv_string)
{
	int i = 0;
	unsigned long int result = 0;

	if (*conv_string == '+')
		conv_string++;
	for (i = 0;  conv_string[i] != '\0'; i++)
	{
		if (conv_string[i] >= '0' && conv_string[i] <= '9')
		{
			result *= 10;
			result += (conv_string[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error_func - print error messages
 * @i_strc: parameter struct
 * @err_specif: error specifier
 * Return: 0 if non-string, -1 otherwise
 */
void print_error_func(info_t *i_strc, char *err_specif)
{
	my_eputs_func(i_strc->fname);
	my_eputs_func(": ");
	myprint_dec(i_strc->line_count, STDERR_FILENO);
	my_eputs_func(": ");
	my_eputs_func(i_strc->argv[0]);
	my_eputs_func(": ");
	my_eputs_func(err_specif);
}

/**
 * myprint_dec - print base_par 10 decimal
 * @input_par: input_par parameter
 * @filed_para: file descriptor
 *
 * Return: character count
 */
int myprint_dec(int input_par, int filed_para)
{
	int (*__putchar)(char) = func_putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (filed_para == STDERR_FILENO)
		__putchar = my_eputchar_func;
	if (input_par < 0)
	{
		_abs_ = -input_par;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input_par;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * cvt_num - convert number
 * @num_par: number parameter
 * @base_par: base_par parameter
 * @farg: fag of the argument
 *
 * Return: the string
 */
char *cvt_num(long int num_par, int base_par, int farg)
{
	static char *array;
	static char buffer[50];
	char sign_char = 0;
	char *my_ptr;
	unsigned long num_byte = num_par;

	if (!(farg & CONVERT_UNSIGNED) && num_par < 0)
	{
		num_byte = -num_par;
		sign_char = '-';

	}
	array = farg & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	my_ptr = &buffer[49];
	*my_ptr = '\0';

	do	{
		*--my_ptr = array[num_byte % base_par];
		num_byte /= base_par;
	} while (num_byte != 0);

	if (sign_char)
		*--my_ptr = sign_char;
	return (my_ptr);
}

/**
 * func_remove_comments - function replace '#' with '\0'
 * @_buff: string modified address
 *
 * Return: 0.
 */
void func_remove_comments(char *_buff)
{
	int i;

	for (i = 0; _buff[i] != '\0'; i++)
		if (_buff[i] == '#' && (!i || _buff[i - 1] == ' '))
		{
			_buff[i] = '\0';
			break;
		}
}
