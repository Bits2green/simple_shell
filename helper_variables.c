#include "shell.h"

/**
 * is_chain_delimiter - Check if the current character is a chain delimiter
 * @info: Parameter struct
 * @buffer: Character buffer
 * @position: Address of the current position in the buffer
 *
 * Return: 1 if a chain delimiter is found, 0 otherwise
 */
int is_chain_delimiter(info_t *info, char *buffer, size_t *position)
{
    size_t index = *position;

    if (buffer[index] == '|' && buffer[index + 1] == '|')
    {
        buffer[index] = '\0';
        index++;
        info->command_chain_type = COMMAND_OR;
    }
    else if (buffer[index] == '&' && buffer[index + 1] == '&')
    {
        buffer[index] = '\0';
        index++;
        info->command_chain_type = COMMAND_AND;
    }
    else if (buffer[index] == ';') /* Found the end of this command */
    {
        buffer[index] = '\0'; /* Replace semicolon with null terminator */
        info->command_chain_type = COMMAND_CHAIN;
    }
    else
    {
        return (0);
    }
    *position = index;
    return (1);
}

/**
 * check_chain - Check if we should continue chaining based on the last status
 * @info: Parameter struct
 * @buffer: Character buffer
 * @position: Address of the current position in the buffer
 * @start: Starting position in the buffer
 * @length: Length of the buffer
 *
 * Return: void
 */
void check_chain(info_t *info, char *buffer, size_t *position, size_t start, size_t length)
{
    size_t index = *position;

    if (info->command_chain_type == COMMAND_AND)
    {
        if (info->status)
        {
            buffer[start] = '\0';
            index = length;
        }
    }
    if (info->command_chain_type == COMMAND_OR)
    {
        if (!info->status)
        {
            buffer[start] = '\0';
            index = length;
        }
    }
    *position = index;
}

/**
 * replace_command_alias - Replace command aliases in the tokenized string
 * @info: Parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_command_alias(info_t *info)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = find_alias_node(info->alias, info->command_argv[0], '=');
        if (!node)
        {
            return (0);
        }
        free(info->command_argv[0]);
        p = custom_strchr(node->str, '=');
        if (!p)
        {
            return (0);
        }
        p = strdup(p + 1);
        if (!p)
        {
            return (0);
        }
        info->command_argv[0] = p;
    }
    return (1);
}

/**
 * replace_command_vars - Replace variables in the tokenized string
 * @info: Parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_command_vars(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->command_argv[i]; i++)
    {
        if (info->command_argv[i][0] != '$' || !info->command_argv[i][1])
        {
            continue;
        }

        if (!strcmp(info->command_argv[i], "$?"))
        {
            replace_string(&(info->command_argv[i]), strdup(convert_number(info->status, 10, 0)));
            continue;
        }
        if (!strcmp(info->command_argv[i], "$$"))
        {
            replace_string(&(info->command_argv[i]), strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        node = find_node_with_prefix(info->environment, &info->command_argv[i][1], '=');
        if (node)
        {
            replace_string(&(info->command_argv[i]), strdup(strchr(node->str, '=') + 1));
            continue;
        }
        replace_string(&(info->command_argv[i]), strdup(""));
    }
    return (0);
}

/**
 * replace_string - Replace an old string with a new string
 * @old_str: Address of the old string
 * @new_str: New string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old_str, char *new_str)
{
    free(*old_str);
    *old_str = new_str;
    return (1);
}
