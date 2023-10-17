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
info->custom_environ = list_to_strings(info->custom_env_list);
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
list_t *node = info->custom_env_list;
size_t i = 0;
char *p;

if (!node || !var)
return (0);

while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
info->env_changed = delete_node_at_index(&(info->custom_env_list), i);
i = 0;
node = info->custom_env_list;
continue;
}
node = node->next;
i++;
}
return (info->env_changed);
}

/**
* custom_set_env_var - Initialize a new custom environment variable,
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

buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);
_strncpy(buf, var, _strlen(var) + _strlen(value) + 2);
_strcat(buf, "=");
_strcat(buf, value);
node = info->custom_env_list;
while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
info->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_end(&(info->custom_env_list), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}
