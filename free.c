#include "shell.h"

/**
* custom_free - frees a pointer and sets it to NULL
* @ptr: address of the pointer to free
*
* Return: 1 if freed, otherwise 0.
*/
int custom_free(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}
