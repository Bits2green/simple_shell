#include "sshell.h"

char *_getenv(char *var)
{
    char *tmp, *key, *value, *env;
    int i;

    for (i = 0; environ[i; i++])
    {
        tmp = _strdup(environ[i]);
        key = strtok(tmp, "=");
        if (_strcmp(key, var) == 0)
        {
            value = strtok(NULL, "\n");
            env = _strdup(value);
            free(tmp);
            return (env);
        }
        free(tmp), tmp = NULL;
    }
    return (NULL);

}