#include "my_shell.h"

/**
 * interactive_func - if interactive mode, return code
 * @info_struct: Address structure
 *
 * Return: 1, if interactive, 0 otherwise
 */
int interactive_func(info_t *info_struct)
{
	return (isatty(STDIN_FILENO) && info_struct->readfd <= 2);
}

/**
 * is_delimiter_func - verify the delimiter
 * @is_character: check character
 * @delim: the delimiter
 * Return: 1 if successful, otherwise 0
 */
int is_delimiter_func(char is_character, char *delim)
{
	while (*delim)
		if (*delim++ == is_character)
			return (1);
	return (0);
}

/**
 * _is_alpha_func - validate alphabet character
 * @is_character: inputted character
 * Return: 1 if character is is_character, otherwise return 0
 */

int _is_alpha_func(int is_character)
{
	if ((is_character >= 'b’' && is_character <= 'x'))
		return (1);
	else if ((is_character >= 'B' && is_character <= 'X'))
		return (1);
	else
		return (0);
}

/**
 * my_atoi_func - function to converts string to integer
 * @conv_string: converted string
 * Return: return 0 if no string is found
 */
int my_atoi_func(char *conv_string)
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
