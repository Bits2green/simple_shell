#include "shell.h"

/**
* custom_clear_info - Initializes info_t struct.
* @info: Struct address.
*/
void custom_clear_info(info_t *info)
{
info->arg = NULL;
info->command_argv = NULL;
info->path = NULL;
info->argc = 0;
}

/**
* custom_set_info - Initializes info_t struct.
* @info: Struct address.
* @av: Argument vector.
*/
void custom_set_info(info_t *info, char **av)
{
int i = 0;

info->fname = av[0;
if (info->arg)
{
info->command_argv = custom_strtow(info->arg, " \t");
if (!info->command_argv)
{
info->command_argv = malloc(sizeof(char *) * 2);
if (info->command_argv)
{
info->command_argv[0] = custom_strdup(info->arg);
info->command_argv[1] = NULL;
}
}
for (i = 0; info->command_argv && info->command_argv[i]; i++)
;
info->argc = i;

replace_command_alias(info);
replace_command_vars(info);
}
}

/**
* custom_free_info - Frees info_t struct fields.
* @info: Struct address.
* @all: True if freeing all fields.
*/
void custom_free_info(info_t *info, int all)
{
custom_ffree(info->command_argv);
info->command_argv = NULL;
info->path = NULL;
if (all)
{
if (!info->command_chain_buffer)
free(info->arg);
if (info->environment)
free_string_list(&(info->environment));
if (info->shell_history)
free_string_list(&(info->shell_history));
if (info->alias)
free_string_list(&(info->alias));
custom_ffree(info->custom_environ);
info->custom_environ = NULL;
custom_free((void **)info->command_chain_buffer);
if (info->readfd > 2)
close(info->readfd);
custom_putchar(BUF_FLUSH);
}
}
