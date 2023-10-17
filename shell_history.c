#include "shell.h"

/**
* get_shell_history_file - gets the shell history file
* @info: parameter struct
*
* Return: allocated string containing the history file
*/
char *get_shell_history_file(info_t *info)
{
char *home_dir, *history_file_path;

home_dir = _getenv(info, "HOME=");
if (!home_dir)
return (NULL);

history_file_path = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(SHELL_HIST_FILE) + 2));
if (!history_file_path)
{
free(home_dir);
return (NULL);
}

history_file_path[0] = 0;
_strcpy(history_file_path, home_dir);
_strcat(history_file_path, "/");
_strcat(history_file_path, SHELL_HIST_FILE);

free(home_dir);
return (history_file_path);
}

/**
* write_shell_history - creates a file, or appends to an existing file for shell history
* @info: the parameter struct
*
* Return: 1 on success, else -1
*/
int write_shell_history(info_t *info)
{
ssize_t file_descriptor;
char *file_name = get_shell_history_file(info);
list_t *node = NULL;

if (!file_name)
return (-1);

file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(file_name);

if (file_descriptor == -1)
return (-1);

for (node = info->shell_history; node; node = node->next)
{
_putsfd(node->str, file_descriptor);
_putfiledescriptor('\n', file_descriptor);
}

_putfiledescriptor(BUF_FLUSH, file_descriptor);
close(file_descriptor);

return (1);
}

/**
* read_shell_history - reads shell history from file
* @info: the parameter struct
*
* Return: history count on success, 0 otherwise
*/
int read_shell_history(info_t *info)
{
int i, last = 0, line_count = 0;
ssize_t file_descriptor, read_length, file_size = 0;
struct stat file_stat;
char *buffer = NULL, *file_name = get_shell_history_file(info);

if (!file_name)
return (0);

file_descriptor = open(file_name, O_RDONLY);
free(file_name);

if (file_descriptor == -1)
return (0);

if (!fstat(file_descriptor, &file_stat))
file_size = file_stat.st_size;

if (file_size < 2)
return (0);

buffer = malloc(sizeof(char) * (file_size + 1));

if (!buffer)
return (0);

read_length = read(file_descriptor, buffer, file_size);
buffer[file_size] = 0;

if (read_length <= 0)
return free(buffer), 0;

close(file_descriptor);

for (i = 0; i < file_size; i++)
{
if (buffer[i] == '\n')
{
buffer[i] = 0;
build_shell_history_list(info, buffer + last, line_count++);
last = i + 1;
}
}

if (last != i)
build_shell_history_list(info, buffer + last, line_count++);

free(buffer);
info->shell_history_count = line_count;

while (info->shell_history_count-- >= SHELL_HIST_MAX)
delete_node_at_index(&(info->shell_history), 0);

renumber_shell_history(info);
return (info->shell_history_count);
}

/**
* build_shell_history_list - adds an entry to a shell history linked list
* @info: Structure containing potential arguments. Used to maintain
* @buffer: buffer
* @line_count: the history line count, shell_history_count
*
* Return: Always 0
*/
int build_shell_history_list(info_t *info, char *buffer, int line_count)
{
list_t *node = NULL;

if (info->shell_history)
node = info->shell_history;

add_node_end(&node, buffer, line_count);

if (!info->shell_history)
info->shell_history = node;

return (0);
}

/**
* renumber_shell_history - renumbers the shell history linked list after changes
* @info: Structure containing potential arguments. Used to maintain
*
* Return: the new shell history count
*/
int renumber_shell_history(info_t *info)
{
list_t *node = info->shell_history;
int i = 0;

while (node)
{
node->num = i++;
node = node->next;
}

return (info->shell_history_count = i);
}
