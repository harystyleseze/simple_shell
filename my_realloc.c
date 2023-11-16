#include "my_shell.h"

/**
 * func_memset - constant byte memory to fill
 * @conv_string: pointer to memory area
 * @b: byte to fill
 * @num_byte: number to fill
 * Return: pointer to memory
 */
char *func_memset(char *conv_string, char b, unsigned int num_byte)
{
	unsigned int i;

	for (i = 0; i < num_byte; i++)
		conv_string[i] = b;
	return (conv_string);
}

/**
 * func_ffree - function to free string of strings
 * @pp: tjhe string of strings
 */
void func_ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * func__realloc - memory block to reallocate
 * @my_ptr: previous pointer
 * @old_size: byte of previous pointer
 * @new_size: byte of new pointer
 *
 * Return: pointer
 */
void *func__realloc(void *my_ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!my_ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(my_ptr), NULL);
	if (new_size == old_size)
		return (my_ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)my_ptr)[old_size];
	free(my_ptr);
	return (p);
}
