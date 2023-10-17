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
    struct stat file_stat;

    (void)info;
    if (!path || stat(path, &file_stat) != 0)
        return (0);

    if (S_ISREG(file_stat.st_mode))
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
 * find_executable_path - finds the full path of a command in the PATH environment variable
 * @info: the info struct
 * @path_str: the PATH string
 * @command: the command to find
 *
 * Return: full path of the command if found, or NULL
 */
char *find_executable_path(info_t *info, char *path_str, char *command)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!path_str)
        return (NULL);
    if (_strlen(command) > 2 && starts_with(command, "./"))
    {
        if (is_executable(info, command))
            return (command);
    }
    while (1)
    {
        if (!path_str[i] || path_str[i] == ':')
        {
            path = copy_chars(path_str, curr_pos, i);
            if (!*path)
                _strcat(path, command);
            else
            {
                _strcat(path, "/");
                _strcat(path, command);
            }
            if (is_executable(info, path))
                return (path);
            if (!path_str[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return (NULL);
}
