#include "shell.h"

/**
* is_executable - determines if a file is an executable command
* @info: the info struct
* @path: path to the file
*
* Return: 1 if true, 0 otherwise
*/
int is_executable(info_t *info, char *path)
{
struct stat filecustom_stat;

(void)info;
if (!path || stat(path, &filecustom_stat) != 0)
return (0);

if (S_ISREG(filecustom_stat.st_mode))
return (1);
return (0);
}

/**
* copy_chars - copies characters from the source to a buffer
* @src: source string
* @start: starting index
* @stop: stopping index
*
* Return: pointer to the new buffer
*/
char *copy_chars(char *src, int start, int stop)
{
static char buffer[1024];
int i = 0, k = 0;

for (k = 0, i = start; i < stop; i++)
{
if (src[i] != ':')
buffer[k++] = src[i];
}
buffer[k] = 0;
return (buffer);
}

/**
* find_executable_path - finds full path
* of a command in the PATH environment variable
* @info: the info struct
* @pathcustom_str: the PATH string
* @command: the command to find
*
* Return: full path of the command if found, or NULL
*/
char *find_executable_path(info_t *info, char *pathcustom_str, char *command)
{
int i = 0, curr_pos = 0;
char *path;

if (!pathcustom_str)
return (NULL);
if (custom_strlen(command) > 2 && custom_starts_with(command, "./"))
{
if (is_executable(info, command))
return (command);
}
while (1)
{
if (!pathcustom_str[i] || pathcustom_str[i] == ':')
{
path = copy_chars(pathcustom_str, curr_pos, i);
if (!*path)
custom_strcat(path, command);
else
{
custom_strcat(path, "/");
custom_strcat(path, command);
}
if (is_executable(info, path))
return (path);
if (!pathcustom_str[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}
