#include "sshell.h"

int _run(char **cmd, char **argv)
{
    pid_t child;
    int status;

    child = fork();
    if (child == 0)
    {
        if (execve(cmd[0], cmd, envir))
    }
}