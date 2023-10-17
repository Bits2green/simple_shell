#include "shell.h"

/**
 * custom_strcpy - Copies a string.
 * @dest: The destination.
 * @src: The source.
 *
 * Return: Pointer to destination.
 */
char *custom_strcpy(char *dest, char *src)
{
    int i = 0;

    if (dest == src || src == 0)
        return (dest);

    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
    return (dest);
}

/**
 * custom_strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *custom_strdup(const char *str)
{
    int length = 0;
    char *ret;

    if (str == NULL)
        return (NULL);

    while (*str++)
        length++;

    ret = malloc(sizeof(char) * (length + 1));

    if (!ret)
        return (NULL);

    for (length++; length--;)
        ret[length] = *--str;

    return (ret);
}

/**
 * custom_puts - Prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void custom_puts(char *str)
{
    int i = 0;

    if (!str)
        return;

    while (str[i] != '\0')
    {
        custom_putchar(str[i]);
        i++;
    }
}

/**
 * custom_putchar - Writes the character c to stdout.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_putchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
        buf[i++] = c;

    return (1);
}
