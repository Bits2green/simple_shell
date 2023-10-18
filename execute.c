#include "sshell.h"

int _run(char **cmd, char **argv)
{
pid_t child;
int status;

child = fork();
if (child == 0)
{
if (execve(cmd[0], cmd, environ) == -1)
{
perror(argv[0]);
free_string_array(cmd);
exit(0);
}

}
else
{
waitpid(child, &status, 0);
free_string_array(cmd);
}
return (WEXITSTATUS(status));


}

