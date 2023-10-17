#include "shell.h"

/**
* executeCommand - Execute a command.
* @command: A pointer to the command to execute.
*/
void executeCommand(char **command)
{
char *parameter = command[1];
char *searchPath;
/*char *executablePath;*/
char *slash = "/";
char *tempPath;

char *commandToExecute = command[0];
char *arguments[4];

if (access(command[0], F_OK) == 0)
{
arguments[0] = command[0];
arguments[1] = parameter;
arguments[2] = ".";
arguments[3] = NULL;

if (execve(arguments[0], arguments, NULL) == -1)
{
perror("Error");
}
}
else
{
searchPath = findExecutablePath(commandToExecute);
slash = concatenate_strings(searchPath, slash);
tempPath = concatenate_strings(slash, command[0]);

arguments[0] = tempPath;
arguments[1] = parameter;
arguments[2] = ".";
arguments[3] = NULL;

if (execve(arguments[0], arguments, NULL) == -1)
{
perror("Error");
}
}
}
