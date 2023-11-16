#include "my_shell.h"

/**
 * strlen_func - returns the length_value of a string
 * @conv_string: the string whose length_value to check
 *
 * Return: integer length_value of string
 */
int strlen_func(char *conv_string)
{
	int i = 0;

	if (!conv_string)
		return (0);

	while (*conv_string++)
		i++;
	return (i);
}

/**
 * func__strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int func__strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * func_starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *func_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * func_strcat - join two strings
 * @dest_string: destination buffer
 * @src_string: source buffer
 *
 * Return: pointer to destination buffer
 */
char *func_strcat(char *dest_string, char *src_string)
{
	char *_ret = dest_string;

	while (*dest_string)
		dest_string++;
	while (*src_string)
		*dest_string++ = *src_string++;
	*dest_string = *src_string;
	return (_ret);
}
