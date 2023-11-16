#include "my_shell.h"

/**
 * func_bfree - free pointer
 * @my_ptr: pointer to free
 *
 * Return: 1 upon success, 0 otherwise
 */
int func_bfree(void **my_ptr)
{
	if (my_ptr && *my_ptr)
	{
		free(*my_ptr);
		*my_ptr = NULL;
		return (1);
	}
	return (0);
}
