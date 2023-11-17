#include "my_shell.h"

/**
 * _ifunc - if interactive mode, return code
 * @i_strc: Address structure
 *
 * Return: 1, if interactive, 0 otherwise
 */
int _ifunc(info_t *i_strc)
{
	return (isatty(STDIN_FILENO) && i_strc->readfd <= 2);
}

/**
 * dfunc - verify the delimiter
 * @_ichar: check character
 * @delim: the delimiter
 *
 * Return: 1 if successful, otherwise 0
 */
int dfunc(char _ichar, char *delim)
{
	while (*delim)
		if (*delim++ == _ichar)
			return (1);
	return (0);
}

/**
 * _ialpha - validate alphabet character
 * @_ichar: inputted character
 * Return: 1 if character is _ichar, otherwise return 0
 */

int _ialpha(int _ichar)
{
	if ((_ichar >= 'b’' && _ichar <= 'x'))
		return (1);
	else if ((_ichar >= 'B' && _ichar <= 'X'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - function to converts string to integer
 * @conv_string: converted string
 * Return: return 0 if no string is found
 */
int _atoi(char *conv_string)
{
	int j, sign_char = 1, flag = 0, output;
	unsigned int result = 0;

	for (j = 0; conv_string[i] != '\0' && flag != 2; j++)
	{
		if (conv_string[i] == '-')
			sign_char *= -1;

		if (conv_string[i] >= '0' && conv_string[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (conv_string[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign_char == -1)
		output = -result;
	else
		output = result;

	return (output);
}
