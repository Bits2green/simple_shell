#include "shell.h"

/**
 * my_strcmp - Compares strings
 * @s1: String 1
 * @s2: String 2
<<<<<<< HEAD
 *
 * Return: 0
*/
int my_strcmp(const char *s1, const char *s2)
{
while (*s1 && (*s1 == *s2))
{
s1++;
s2++;
}
return (*(unsigned char *)s1 - *(unsigned char *)s2);
=======
 * 
 * Return: 0
*/
int my_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
>>>>>>> 8280941dffeef44a27a8240d1284a4b4ef6a4380
}

/**
 * my_strlen - Calculates length of string
 * @str: String whose length to be calcutated
<<<<<<< HEAD
 *
 * Return: 0
*/
size_t my_strlen(const char *str)
	const char *s = str;
while (*s)
{
s++;
}
return (s - str);
=======
 * 
 * Return: 0
*/

size_t my_strlen(const char *str) {
    const char *s = str;
    while (*s) {
        s++;
    }
    return (s - str);
>>>>>>> 8280941dffeef44a27a8240d1284a4b4ef6a4380
}

/**
 * my_strcpy - Copies strings
 * @dest: Destination of the copied string
 * @src: String to be copied
<<<<<<< HEAD
 *
 * Return: 0
*/
char *my_strcpy(char *dest, const char *src)
{
char *d = dest;
while ((*d = *src))
{
d++;
src++;
}
return (dest);
}
=======
 * 
 * Return: 0
*/

char *my_strcpy(char *dest, const char *src)
    char *d = dest;
    while ((*d = *src)) {
        d++;
        src++;
    }
    return (dest);

/**
 * my_strdup - duplicates a string
 * @str: String to be duplicated
 * 
 * Return: 0
*/
>>>>>>> 8280941dffeef44a27a8240d1284a4b4ef6a4380

/**
 * my_strdup - duplicates a string
 * @str: String to be duplicated
 *
 * Return: 0
*/
char *my_strdup(const char *str)
{
size_t len;
char *copy;

if (str == NULL)
return (NULL);

len = my_strlen(str) + 1;
copy = (char *)malloc(len);

if (copy != NULL)
my_strcpy(copy, str);

return (copy);
}
