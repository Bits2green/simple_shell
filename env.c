#include "shell.h"

/**
* print_custom_env - prints the current environment
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
* Return: Always 0
*/
int print_custom_env(info_t *info)
{
print_linked_list_str(info->custom_env_list);
return (0);
}

/**
* get_custom_env_value - gets the value of a custom environment variable
* @info: Structure containing potential arguments. Used to maintain
* @name: env var name
*
* Return: the value
*/
char *get_custom_env_value(info_t *info, const char *name)
{
list_t *node = info->custom_env_list;
char *p;

while (node)
{
p = custom_starts_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
* set_custom_env_var - Initialize a new custom environment variable,
*             or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Return: Always 0
*/
int set_custom_env_var(info_t *info)
{
if (info->argc != 3)
{
custom_eputs("Incorrect number of arguments\n");
return (1);
}
if (set_custom_env(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}

/**
* unset_custom_env_var - Remove a custom environment variable
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Return: Always 0
*/
int unset_custom_env_var(info_t *info)
{
int i;

if (info->argc == 1)
{
custom_eputs("Too few arguments.\n");
return (1);
}
for (i = 1; i <= info->argc; i++)
unset_custom_env(info, info->argv[i]);

return (0);
}

/**
* populate_custom_env_list - populates custom environment linked list
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
* Return: Always 0
*/
int populate_custom_env_list(info_t *info)
{
list_t *node = NULL;
size_t i;

for (i = 0; info->custom_environ[i]; i++)
add_node_at_end(&node, info->custom_environ[i], 0);
info->custom_env_list = node;
return (0);
}
