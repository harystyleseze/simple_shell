#include "my_shell.h"

/**
 * func_strcpy - copies a string
 * @dest_string: the destination
 * @src_string: the source
 *
 * Return: pointer to destination
 */
char *func_strcpy(char *dest_string, char *src_string)
{
	int i = 0;

	if (dest_string == src_string || src_string == 0)
		return (dest_string);
	while (src_string[i])
	{
		dest_string[i] = src_string[i];
		i++;
	}
	dest_string[i] = 0;
	return (dest_string);
}

/**
 * func_strdup - duplicates a string
 * @_str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *func_strdup(const char *_str)
{
	int length_value = 0;
	char *_ret;

	if (_str == NULL)
		return (NULL);
	while (*_str++)
		length_value++;
	_ret = malloc(sizeof(char) * (length_value + 1));
	if (!_ret)
		return (NULL);
	for (length_value++; length_value--;)
		_ret[length_value] = *--_str;
	return (_ret);
}

/**
 * func_puts - prints an input_par string
 * @_str: the string to be printed
 *
 * Return: Nothing
 */
void func_puts(char *_str)
{
	int i = 0;

	if (!_str)
		return;
	while (_str[i] != '\0')
	{
		func_putchar(_str[i]);
		i++;
	}
}

/**
 * func_putchar - writes the character is_character to stdout
 * @is_character: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int func_putchar(char is_character)
{
	static int i;
	static char my_buffer[WRITE_BUF_SIZE];

	if (is_character == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, my_buffer, i);
		i = 0;
	}
	if (is_character != BUF_FLUSH)
		my_buffer[i++] = is_character;
	return (1);
}
