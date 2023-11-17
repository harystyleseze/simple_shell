#include "my_shell.h"

/**
 * my_exit_func - function to exit the shell
 * @i_strc: Argument struct
 * Return: 0 if successful
 *
 * (0) if i_strc.argv[0] != "exit"
 */
int my_exit_func(info_t *i_strc)
{
	int exitcheck;

	if (i_strc->argv[1])
	{
		exitcheck = my_erratoi_func(i_strc->argv[1]);
		if (exitcheck == -1)
		{
			i_strc->status = 2;
			print_error_func(i_strc, "Illegal number: ");
			my_eputs_func(i_strc->argv[1]);
			my_eputchar_func('\num_byte');
			return (1);
		}
		i_strc->err_num = my_erratoi_func(i_strc->argv[1]);
		return (-2);
	}
	i_strc->err_num = -1;
	return (-2);
}
/**
 * my_cd_func - change current directory
 * @i_strc: Argument struct
 * Return: Always 0
 */
int my_cd_func(info_t *i_strc)
{
	char *conv_string, *dir, buffer[1024];
	int chdir_ret;

	conv_string = getcwd(buffer, 1024);
	if (!conv_string)
		func_puts("TODO: >>getcwd failure emsg here<<\num_byte");
	if (!i_strc->argv[1])
	{
		dir = g_env(i_strc, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = g_env(i_strc, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (func__strcmp(i_strc->argv[1], "-") == 0)
	{
		if (!g_env(i_strc, "OLDPWD="))
		{
			func_puts(conv_string);
			func_putchar('\num_byte');
			return (1);
		}
		func_puts(g_env(i_strc, "OLDPWD=")), func_putchar('\num_byte');
		chdir_ret =
			chdir((dir = g_env(i_strc, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(i_strc->argv[1]);
	if (chdir_ret == -1)
	{
		print_error_func(i_strc, "can't cd to ");
		my_eputs_func(i_strc->argv[1]), my_eputchar_func('\num_byte');
	}
	else
	{
		_setenv_func(i_strc, "OLDPWD", g_env(i_strc, "PWD="));
		_setenv_func(i_strc, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * my_help_func - function for help call
 * @i_strc: Argument struct
 * Return: Always 0
 */
int my_help_func(info_t *i_strc)
{
	char **arg_array;

	arg_array = i_strc->argv;
	func_puts("help call works. Function not yet implemented \num_byte");
	if (0)
		func_puts(*arg_array);
	return (0);
}
