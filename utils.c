#include "sshell.h"

/**
 * free_string_array - free memory allocated to the token array
 * @array: the array whose allocated memory needs to be freed
 *
 * Return: 0
 */

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

