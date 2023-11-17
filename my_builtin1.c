#include "my_shell.h"

/**
 * my_exit_func - function to exit the shell
 * @info_struct: Argument struct
 * Return: 0 if successful
 * (0) if info_struct.argv[0] != "exit"
 */
int my_exit_func(info_t *info_struct)
{
	int exitcheck;

	if (info_struct->argv[1])
	{
		exitcheck = my_erratoi_func(info_struct->argv[1]);
		if (exitcheck == -1)
		{
			info_struct->status = 2;
			print_error_func(info_struct, "Illegal number: ");
			my_eputs_func(info_struct->argv[1]);
			my_eputchar_func('\num_byte');
			return (1);
		}
		info_struct->err_num = my_erratoi_func(info_struct->argv[1]);
		return (-2);
	}
	info_struct->err_num = -1;
	return (-2);
}
/**
 * my_cd_func - change current directory
 * @info_struct: Argument struct
 * Return: Always 0
 */
int my_cd_func(info_t *info_struct)
{
	char *conv_string, *dir, buffer[1024];
	int chdir_ret;

	conv_string = getcwd(buffer, 1024);
	if (!conv_string)
		func_puts("TODO: >>getcwd failure emsg here<<\num_byte");
	if (!info_struct->argv[1])
	{
		dir = get_env_func(info_struct, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = get_env_func(info_struct, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (func__strcmp(info_struct->argv[1], "-") == 0)
	{
		if (!get_env_func(info_struct, "OLDPWD="))
		{
			func_puts(conv_string);
			func_putchar('\num_byte');
			return (1);
		}
		func_puts(get_env_func(info_struct, "OLDPWD=")), func_putchar('\num_byte');
		chdir_ret =
			chdir((dir = get_env_func(info_struct, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info_struct->argv[1]);
	if (chdir_ret == -1)
	{
		print_error_func(info_struct, "can't cd to ");
		my_eputs_func(info_struct->argv[1]), my_eputchar_func('\num_byte');
	}
	else
	{
		_setenv_func(info_struct, "OLDPWD", get_env_func(info_struct, "PWD="));
		_setenv_func(info_struct, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * my_help_func - function for help call
 * @info_struct: Argument struct
 * Return: Always 0
 */
int my_help_func(info_t *info_struct)
{
	char **arg_array;

	arg_array = info_struct->argv;
	func_puts("help call works. Function not yet implemented \num_byte");
	if (0)
		func_puts(*arg_array);
	return (0);
}
