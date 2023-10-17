#include "shell.h"

/**
 * my_exit - Handle the 'exit' built-in command.
 * @info: Pointer to the info struct.
 *
 * Return: Always returns -2 to signal the shell to exit.
 */
int my_exit(info_t *info)
{
	int exit_status;

	if (info->command_argv[1])
	{
		exit_status = custom_erratoi(info->command_argv[1]);

		if (exit_status == -1)
		{
			info->status = 2;
			custom_print_error(info, "Illegal number: ");
			customcustom_eputs(info->command_argv[1]);
			customcustom_eputchar('\n');
			return (1);
		}

		info->err_num = exit_status;
		return (-2);
	}

	info->err_num = -1;
	return (-2);
}

/**
 * my_cd - Handle the 'cd' built-in command to change the current directory.
 * @info: Pointer to the info struct.
 *
 * Return: Always returns 0.
 */
int my_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		customcustom_puts("TODO: Handle getcwd failure here\n");

	if (!info->command_argv[1])
	{
		dir = print_custom_env(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = print_custom_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (custom_strcmp(info->command_argv[1], "-") == 0)
	{
		if (!print_custom_env(info, "OLDPWD="))
		{
			custom_puts(s);
			custom_putchar('\n');
			return (1);
		}

		custom_puts(print_custom_env(info, "OLDPWD="));
		custom_putchar('\n');
		chdir_ret = chdir((dir = print_custom_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
	{
		chdir_ret = chdir(info->command_argv[1]);
	}

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		custom_eputs(info->command_argv[1]);
		custom_eputchar('\n');
	}
	else
	{
		custom_set_env_var(info, "OLDPWD", print_custom_env(info, "PWD="));
		custom_set_env_var(info, "PWD", getcwd(buffer, 1024));
	}

	return (0);
}

/**
 * my_help - Handle the 'help' built-in command.
 * @info: Pointer to the info struct.
 *
 * Return: Always returns 0.
 */
int my_help(info_t *info)
{
	char **arg_array;

	arg_array = info->command_argv;
	custom_puts("Help command works. Function not yet implemented\n");

	if (0)
		custom_puts(*arg_array); /* Temporary unused variable workaround */
	return (0);
}
