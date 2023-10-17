#include "shell.h"

/**
 * compare_strings - Compare two strings to find a match.
 *
 * @str1: First string.
 * @str2: Second string.
 *
 * Return: 0 if there's a match, or a non-zero number if different.
 **/
int compare_strings(char *str1, char *str2)
{
	int index = 0;

	for (; (*str2 != '\0' && *str1 != '\0') && *str1 == *str2; str1++)
	{
		if (index == 3)
			break;
		index++;
		str2++;
	}

	return (*str1 - *str2);
}

/**
 * write_char - Write a character similar to putchar.
 * @ch: The character to print.
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_char(char ch)
{
	return (write(1, &ch, 1));
}

/**
 * print_string - Print a string similar to puts in C.
 * @str: A pointer to the string to print.
 */
void print_string(char *str)
{
	while (*str != '\0')
	{
		write_char(*str);
		str++;
	}
}

/**
 * string_length - Calculate the length of a string.
 * @str: The input string.
 * Return: Length of the string.
 */
int string_length(char *str)
{
	int length;

	for (length = 0; str[length] != '\0'; length++)
		;

	return (length);
}

/**
 * concatenate_strings - Concatenate two strings.
 * @s1: First string.
 * @s2: Second string.
 * Return: Pointer to the concatenated string.
 */
char *concatenate_strings(char *s1, char *s2)
{
	char *result;
	int len_s1, len_s2, j, i, e;

	if (s1 == NULL)
		s1 = "";

	if (s2 == NULL)
		s2 = "";

	len_s1 = string_length(s1);
	len_s2 = string_length(s2);

	result = malloc((len_s1 + len_s2 + 1) * sizeof(char));

	if (result == NULL)
		return (NULL);

	for (j = 0; j < len_s1; j++)
	{
		result[j] = s1[j];
	}

	for (i = len_s1, e = 0; e <= len_s2; i++, e++)
	{
		result[i] = s2[e];
	}

	return (result);
}
