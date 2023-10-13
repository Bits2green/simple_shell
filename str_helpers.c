#include "shell.h"

/*Custom str functions*/
int my_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

size_t my_strlen(const char *str) {
    const char *s = str;
    while (*s) {
        s++;
    }
    return (s - str);
}

char *my_strcpy(char *dest, const char *src) {
    char *d = dest;
    while ((*d = *src)) {
        d++;
        src++;
    }
    return (dest);
}

char *my_strdup(const char *str)
{
    size_t len;

    if (str == NULL) {
        return (NULL);
    }

    len = my_strlen(str) + 1;
    char *copy = (char *)malloc(len);

    if (copy != NULL) {
        my_strcpy(copy, str);
    }

    return (copy);
}