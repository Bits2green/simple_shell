#include "shell.h"
/**
* main - entry point
* @argc: args
* @argv: args list
*
* Return: 0
*/
int main(int argc, char *argv[])
{
int interactive = isatty(STDIN_FILENO);
char input[MAX_INPUT_SIZE];

while (1)
{
if (interactive)
{
printf("vcshell$ ");
fflush(stdout); }
if (fgets(input, sizeof(input), stdin) == NULL)
{
if (interactive)
printf("\n");
break; }
}

return (0);
}
