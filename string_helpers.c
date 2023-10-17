#include "shell.h"

/**
 * custom_strlen - Returns the length of a string.
 * @str: The string whose length to check.
 *
 * Return: Integer length of the string.
 */
int custom_strlen(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (*str++)
		length++;

	return (length);
}

/**
 * custom_strcmp - Performs lexicographic comparison of two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: -ve if str1 < str2, +ve if str1 > str2, 0 if str1 == str2.
 */
int custom_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}

	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * custom_starts_with - Checks if str starts with prefix.
 * @str: String to search.
 * @prefix: The prefix to find.
 *
 * Return: Address of the next character of str or NULL.
 */
char *custom_starts_with(const char *str, const char *prefix)
{
	while (*prefix)
	{
		if (*prefix++ != *str++)
			return (NULL);
	}

	return ((char *)str);
}

/**
 * custom_strcat - Concatenates two strings.
 * @destination: The destination buffer.
 * @source: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *custom_strcat(char *destination, char *source)
{
	char *result = destination;

	while (*destination)
	{
		destination++;
	}

	while (*source)
	{
		*destination++ = *source++;
	}

	*destination = *source;

	return (result);
}
