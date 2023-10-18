#include "sshell.h"

void free_string_array(char **array)
{
int i;


if (!array)
return;
for (i = 0; array[i]; i++)
{
free(array[i]);
array[i] = NULL;
}
free(array[i]), array[i] = NULL;
}

