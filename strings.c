#include "sshell.h"

int _strdup(const char *str)
{
    char ptr;
    int i, len = 0;

    if (str == NULL)
        return (NULL);
    while (*str != '\0')
    {
        len++;
        str++;
    }
    str = str - len;
    ptr = malloc(sizeof(char) * (len +1 ));
    if (ptr == NULL)
        return (NULL);
    for (i = 0; i <= len; i++)
        ptr[i] = str[i];
    return (ptr);
}

int _strcmp(char *s1, char *s2)
{
    int cmpr;

    cmpr = (int)*s1 - (int)*s2;
    while (*s1)
    {
        if (*s1 != *s2)
            break;
        s1++;
        s2++;
        cmpr = (int)*s1 - (int)*s2;
    }
    return (cmpr);   
}

int _strlen(char *s)
{
    int len = 0;

    while (s[len])
        len++;
    return (len);
}

char *_strcat(char *dest, char *src)
{
    char *p = dest;

    while (*p)
        p++;
    while (*src)
    {
        *p = *src;
        p++;
        src++;
    }
    *p = *src;
    return (dest);
}

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}