#include "my_shell.h"

/**
 **my_strncpy - function to copy string
 *@dest_string: copy destination
 *@src_string: copy source string
 *@num_byte: number of characters to copy
 *Return: concatenated character
 */

char *my_strncpy(char *dest_string, char *src_string, int num_byte)
{
	int i, j;
	char *conv_string = dest_string;

	i = 0;
	while (src_string[i] != '\0' && i < num_byte - 1)
	{
		dest_string[i] = src_string[i];
		i++;
	}
	if (i < num_byte)
	{
		j = i;
		while (j < num_byte)
		{
			dest_string[j] = '\0';
			j++;
		}
	}
	return (conv_string);
}

/**
 **_strncat - join two strings
 *@dest_string: string one
 *@src_string: string two
 *@num_byte: amount of max byte used
 *Return: the concatenated string
 */
char *_strncat(char *dest_string, char *src_string, int num_byte)
{
	int i, j;
	char *conv_string = dest_string;

	i = 0;
	j = 0;
	while (dest_string[i] != '\0')
		i++;
	while (src_string[j] != '\0' && j < num_byte)
	{
		dest_string[i] = src_string[j];
		i++;
		j++;
	}
	if (j < num_byte)
		dest_string[i] = '\0';
	return (conv_string);
}

/**
 **_strchr - find character in string
 *@conv_string: parsed string
 *@_ichar: character found
 *Return: pointer to conv_string
 */
char *_strchr(char *conv_string, char _ichar)
{
	do {
		if (*conv_string == _ichar)
			return (conv_string);
	} while (*conv_string++ != '\0');

	return (NULL);
}
