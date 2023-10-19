#include "sshell.h"

/**
 * _run - execute commands after being parsed
 * @cmd: command to be executed
 * @argv: array of arguments that follow the command
 *
 * Return: 0
 */

int _run(char **cmd, char **argv, int index)
{
    char *full_cmd;
pid_t child;
int status;

full_cmd = _getpath(cmd[0]);
if (!full_cmd)
{
    _perror(argv[0], cmd[0], index);
    free_string_array(cmd);
    return (127);
}


child = fork();
if (child == 0)
{
if (execve(full_cmd, cmd, environ) == -1)
{
    free(full_cmd), full_cmd = NULL;
free_string_array(cmd);
}

}
else
{
waitpid(child, &status, 0);
free_string_array(cmd);
free(full_cmd), full_cmd = NULL;
}
return (WEXITSTATUS(status));


}

