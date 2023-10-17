#include "shell.h"

/**
* copy_environ - returns the string array copy of our custom environment
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
* Return: String array
*/
char **copy_environ(info_t *info)
{
if (!info->custom_environ || info->env_changed)
{
info->custom_environ = linked_list_to_strings(info->environment);
info->env_changed = 0;
}

return (info->custom_environ);
}

/**
* custom_unset_env_var - Remove a custom environment variable
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Return: 1 on delete, 0 otherwise
* @var: the string custom environment variable property
*/
int custom_unset_env_var(info_t *info, char *var)
{
list_t *node = info->environment;
size_t i = 0;
char *p;

if (!node || !var)
return (0);

while (node)
{
p = custom_starts_with(node->str, var);
if (p && *p == '=')
{
info->env_changed = delete_node_by_index(&(info->environment), i);
i = 0;
node = info->environment;
continue;
}
node = node->next;
i++;
}
return (info->env_changed);
}

/**
* customcustom_set_env_var - Initialize a new custom environment variable,
*             or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* @var: the string custom environment variable property
* @value: the string custom environment variable value
*  Return: Always 0
*/
int custom_set_env_var(info_t *info, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *p;

if (!var || !value)
return (0);

buf = malloc(custom_strlen(var) + custom_strlen(value) + 2);
if (!buf)
return (1);
custom_strncpy(buf, var, custom_strlen(var) + custom_strlen(value) + 2);
custom_strcat(buf, "=");
custom_strcat(buf, value);
node = info->environment;
while (node)
{
p = custom_starts_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
info->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_at_end(&(info->environment), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}
