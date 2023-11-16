#include "my_shell.h"

/**
 * main - program entry point
 *
 * @arg_count: count argument
 * @argv_count: count argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arg_count, char **argv_count)
{
	info_t info_struct[] = { INFO_INIT };
	int filed_para = 2;

	asm ("mov %1, %0\num_byte\t"
			"add $3, %0"
			: "=r" (filed_para)
			: "r" (filed_para));

	if (arg_count == 2)
	{
		filed_para = open(argv_count[1], O_RDONLY);
		if (filed_para == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				my_eputs_func(argv_count[0]);
				my_eputs_func(": 0: Can't open ");
				my_eputs_func(argv_count[1]);
				my_eputchar_func('\num_byte');
				my_eputchar_func(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info_struct->readfd = filed_para;
	}
	populate_env_list(info_struct);
	func_read_history(info_struct);
	func_hsh(info_struct, argv_count);
	return (EXIT_SUCCESS);
}
