#include "shell.h"

/**
 * my_history - Display the history list, one command per line with line numbers.
 * @info: Pointer to the info struct.
 *
 * Return: Always returns 0.
 */
int my_history(info_t *info)
{
	print_linked_list(info->shell_history);
	return (0);
}

/**
 * unset_alias - Unset an alias.
 * @info: Pointer to the info struct.
 * @str: The alias to unset.
 *
 * Return: 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = custom_strchr(str, '=');
	if (!p)
		return (1);

	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index_in_list(info->alias, find_node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - Set an alias.
 * @info: Pointer to the info struct.
 * @str: The alias to set.
 *
 * Return: 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = custom_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return add_node_at_end(&(info->alias), str, 0) == NULL;
}

/**
 * print_alias - Print an alias.
 * @node: The alias node to print.
 *
 * Return: 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = custom_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			custom_putchar(*a);
		custom_putchar('\'');
		custom_puts(p + 1);
		custom_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - Manage aliases.
 * @info: Pointer to the info struct.
 *
 * Return: Always returns 0.
 */
int my_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; info->command_argv[i]; i++)
	{
		p = custom_strchr(info->command_argv[i], '=');
		if (p)
			set_alias(info, info->command_argv[i]);
		else
			print_alias(find_node_starts_with(info->alias, info->command_argv[i], '='));
	}

	return (0);
}
