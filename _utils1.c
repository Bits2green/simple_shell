#include "sshell.h"

/**
* num_is_pos - Checks if string is a positive number
* @str: string to be checked
* Return: 0
*/

int num_is_pos(char *str)
{
int i;

if (!str)
return (0);
for (i = 0; str[i]; i++)
{
if (str[i] < '0' || str[i] > '9')
return (0);
}
return (1);
}

/**
* custom_atoi - Convert string to integer
* @str: string to be converted
* Return: converted string.
*/

int custom_atoi(char *str)
{
int i, number = 0;

for (i = 0; str[i]; i++)
{
number *= 10;
number += (str[i] - '0');

}
return (number);
}
