#include "sshell.h"

/**
* _getenv - gets the environment vars
* @var: variables to be acquired
* Return: 0
*/

char *_getenv(char *var)
{
char *tmp, *key, *value, *env;
int i;

for (i = 0; environ[i]; i++)
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
