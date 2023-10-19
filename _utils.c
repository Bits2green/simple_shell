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
free(array), array = NULL;
}

/**
* _perror - prints error messages to stdout
* @name: name of errant argument
* @cmd: command name
* @index: error code
*
* Return: 0
*/
void _perror(char *name, char *cmd, int index)
{
char *idx, msg[] = ": not found\n";

idx = _atoi(index);

write(STDERR_FILENO, name, _strlen(name));
write(STDERR_FILENO, ": ", 2);
write(STDERR_FILENO, idx, _strlen(idx));
write(STDERR_FILENO, ": ", 2);
write(STDERR_FILENO, cmd, _strlen(cmd));
write(STDERR_FILENO, msg, _strlen(msg));

free(idx);
}

/**
* _atoi - convert integer to string
* @n: integer to be converted
*
* Return: 0
*/

char *_atoi(int n)
{
char buffer[20];
int i = 0;

if (n == 0)
buffer[i++] = '\0';
else
{
while (n > 0)
{
buffer[i++] = (n % 10) + '0';
n /= 10;

}
}
buffer[i] = '\0';
reverse_string(buffer, i);

return (_strdup(buffer));
}

/**
* reverse_string - reverses a string
* @str: string to be reversed
* @len: length of string to be reversed
*
* Return: 0
*/

void reverse_string(char *str, int len)
{
char tmp;
int start = 0;
int end = len - 1;

while (start < end)
{
tmp = str[start];
str[start] = str[end];
str[end] = tmp;
start++;
end--;
}
}

