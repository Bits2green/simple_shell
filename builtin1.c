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

	if (info->argv[1])
	{
		exit_status = _atoi(info->argv[1]);

		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
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
		_puts("TODO: Handle getcwd failure here\n");

	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}

		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
	{
		chdir_ret = chdir(info->argv[1]);
	}

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
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

	arg_array = info->argv;
	_puts("Help command works. Function not yet implemented\n");

	if (0)
		_puts(*arg_array); /* Temporary unused variable workaround */
	return (0);
}