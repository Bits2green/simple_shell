#include "shell.h"

/**
* findExecutablePath - Find the path to execute a command.
*
* @command: The command to execute.
*
* Return: A string representing the folder where the command can be executed.
**/
char *findExecutablePath(char *command)
{
char **environment;
DIR *directory;
struct dirent *entry;
char *cmd, comp;
char **pathEnvironment = malloc(sizeof(char) * 1024);
char **pathSegments = malloc(sizeof(char) * 1024);
int i;

while (*environment != NULL)
{
if (!compare_strings(*environment, "PATH"))
{
*pathEnvironment = *environment;
for (i = 0; i < 9; i++, pathSegments++, pathEnvironment++)
{
*pathSegments = strtok(*pathEnvironment, ":");
directory = opendir(*pathSegments);
if (directory == NULL)
{
perror("Unable to read directory");
}
while ((entry = readdir(directory)))
{
cmd = entry->d_name;
comp = compare_strings(cmd, command);
if (comp == 0)
{
return (*pathSegments);
}
if (cmd == NULL)
{
perror("Error");
}
}
}
}
environment++;
}
return ("Error: Not Found");
}
