#include "shell.h"

/**
* run_shell - main shell loop
* @info: the parameter & return info structure
* @av: the argument vector from main()
*
* Return: 0 on success, 1 on error, or error code
*/
int run_shell(info_t *info, char **av)
{
ssize_t input_length = 0;
int built_in_ret = 0;

while (input_length != -1 && built_in_ret != -2)
{
custom_clear_info(info);
if (is_shell_interactive(info))
custom_puts("$ ");
custom_eputchar(BUF_FLUSH);
input_length = get_input_line(info);
if (input_length != -1)
{
custom_set_info(info, av);
built_in_ret = find_builtin_command(info);
if (built_in_ret == -1)
find_executable_command(info);
}
else if (is_shell_interactive(info))
custom_putchar('\n');
custom_free_info(info, 0);
}
write_shell_history(info);
custom_free_info(info, 1);
if (!is_shell_interactive(info) && info->status)
exit(info->status);
if (built_in_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (built_in_ret);
}

/**
* find_builtin_command - finds a built-in command
* @info: the parameter & return info structure
*
* Return: -1 if built-in not found,
*			0 if built-in executed successfully,
*			1 if built-in found but not successful,
*			-2 if built-in signals exit()
*/
int find_builtin_command(info_t *info)
{
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", my_exit},
{"env", get_custom_env_value},
{"help", my_help},
{"history", my_history},
{"setenv", set_custom_env_var},
{"unsetenv", unset_custom_env_var},
{"cd", my_cd},
{"alias", my_alias},
{NULL, NULL}};

for (i = 0; builtintbl[i].command; i++)
if (custom_strcmp(info->command_argv[0], builtintbl[i].command) == 0)
{
info->line_count++;
built_in_ret = builtintbl[i].function(info);
break;
}
return (built_in_ret);
}

/**
* find_executable_command - finds an executable command in PATH
* @info: the parameter & return info structure
*
* Return: void
*/
void find_executable_command(info_t *info)
{
char *path = NULL;
int i, k;

info->path = info->command_argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
for (i = 0, k = 0; info->arg[i]; i++)
if (!is_character_delimiter(info->arg[i], " \t\n"))
k++;
if (!k)
return;

path = find_executable_path(info, print_custom_env(info, "PATH="), info->command_argv[0]);
if (path)
{
info->path = path;
execute_command(info);
}
else
{
if ((is_shell_interactive(info) || print_custom_env(info, "PATH=") || info->command_argv[0][0] == '/') && is_executable(info, info->command_argv[0]))
execute_command(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
custom_print_error(info, "not found\n"); } } }

/**
* execute_command - forks and executes a command
* @info: the parameter & return info structure
*
* Return: void
*/
void execute_command(info_t *info)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->command_argv, copy_environ(info)) == -1)
{
custom_free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
custom_print_error(info, "Permission denied\n");
}
}
}
