#include "shell.h"

/**
 * linked_list_length - determines the length of a linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t linked_list_length(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        head = head->next;
        count++;
    }
    return count;
}

/**
 * linked_list_to_strings - returns an array of strings from the list->str
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **linked_list_to_strings(list_t *head)
{
    list_t *node = head;
    size_t length = linked_list_length(head);
    size_t i;
    char **strings;
    char *str;

    if (!head || !length)
        return NULL;

    strings = malloc(sizeof(char *) * (length + 1));
    if (!strings)
        return NULL;

    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(_strlen(node->str) + 1);
        if (!str)
        {
            for (size_t j = 0; j < i; j++)
                free(strings[j]);
            free(strings);
            return NULL;
        }

        str = _strcpy(str, node->str);
        strings[i] = str;
    }
    strings[i] = NULL;
    return strings;
}

/**
 * print_linked_list - prints all elements of a list_t linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_linked_list(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        _puts(convert_number(head->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(head->str ? head->str : "(nil)");
        _puts("\n");
        head = head->next;
        count++;
    }
    return count;
}

/**
 * find_node_starts_with - returns a node whose string starts with a prefix
 * @head: pointer to the list head
 * @prefix: string to match
 * @next_char: the next character after prefix to match
 *
 * Return: matched node or NULL
 */
list_t *find_node_starts_with(list_t *head, char *prefix, char next_char)
{
    char *p = NULL;

    while (head)
    {
        p = starts_with(head->str, prefix);
        if (p && ((next_char == -1) || (*p == next_char)))
            return head;
        head = head->next;
    }
    return NULL;
}

/**
 * get_node_index_in_list - gets the index of a node in the linked list
 * @head: pointer to the list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t get_node_index_in_list(list_t *head, list_t *node)
{
    size_t index = 0;

    while (head)
    {
        if (head == node)
            return index;
        head = head->next;
        index++;
    }
    return -1;
}
