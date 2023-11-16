#include "my_shell.h"

/**
 * **strtow_func - splits a string into words. Repeat delimiters are ignored
 * @_str: the input_par string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow_func(char *_str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **conv_string;

	if (_str == NULL || _str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; _str[i] != '\0'; i++)
		if (!is_delimiter_func(_str[i], d) && (is_delimiter_func(_str[i + 1], d) || !_str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	conv_string = malloc((1 + numwords) * sizeof(char *));
	if (!conv_string)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delimiter_func(_str[i], d))
			i++;
		k = 0;
		while (!is_delimiter_func(_str[i + k], d) && _str[i + k])
			k++;
		conv_string[j] = malloc((k + 1) * sizeof(char));
		if (!conv_string[j])
		{
			for (k = 0; k < j; k++)
				free(conv_string[k]);
			free(conv_string);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			conv_string[j][m] = _str[i++];
		conv_string[j][m] = 0;
	}
	conv_string[j] = NULL;
	return (conv_string);
}

/**
 * **strtow2 - splits a string into words
 * @_str: the input_par string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *_str, char d)
{
	int i, j, k, m, numwords = 0;
	char **conv_string;

	if (_str == NULL || _str[0] == 0)
		return (NULL);
	for (i = 0; _str[i] != '\0'; i++)
		if ((_str[i] != d && _str[i + 1] == d) ||
				    (_str[i] != d && !_str[i + 1]) || _str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	conv_string = malloc((1 + numwords) * sizeof(char *));
	if (!conv_string)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (_str[i] == d && _str[i] != d)
			i++;
		k = 0;
		while (_str[i + k] != d && _str[i + k] && _str[i + k] != d)
			k++;
		conv_string[j] = malloc((k + 1) * sizeof(char));
		if (!conv_string[j])
		{
			for (k = 0; k < j; k++)
				free(conv_string[k]);
			free(conv_string);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			conv_string[j][m] = _str[i++];
		conv_string[j][m] = 0;
	}
	conv_string[j] = NULL;
	return (conv_string);
}
