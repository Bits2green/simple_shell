#include "sshell.h"

/**
 * _builtin -
 * @cmd:
 * Return: 0
*/

int _builtin_s(char *cmd)
{
    char *b_i[] = {
        "exit", "env", "setenv",
        "cd", NULL
    };
    int i;

    for (i = 0; b_i[i]; i++)
    {
        if (_strcmp(cmd, b_i[i]) == 0)
            return (1);
    }
    return (0);
}

void _handle_b(char **cmd, char **argv, int *status, int index)
{
    (void) argv;
    (void) index;

    if (_strcmp(cmd[0], "exit") == 0)
        _quit_shell(cmd, status);
    else if (_strcmp(cmd[0], "env") == 0)
        _display_env(cmd, status);  
}

void _quit_shell(char **cmd, int *status)
{
    free_string_array(cmd);
    exit(*status);
}

void _display_env(char **cmd, int *status)
{
    int i;

    for (i = 0; environ[i]; i++)
    {
        write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
        write(STDOUT_FILENO, "\n", 1);
    }
    free_string_array(cmd);
    (*status) = 0;
}