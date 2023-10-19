#include "sshell.h"

/**
* main - Entry point
* @ac: - Args count
* @argv: Arguments
* Return: 0
*/

int main(int ac, char **argv)
{
char *line = NULL, **cmd = NULL;
int status = 0, index = 0;
(void)ac;

while (1)
{
line = readLine();
if (line == NULL) /*EOF or ctrlD*/
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "\n", 1);
return (status);
}

index++;
cmd = tokenize(line);
if (!cmd)
continue;

if (_builtin_s(cmd[0]))
    _handle_b(cmd, argv, &status, index);

else
    status = _run(cmd, argv, index);
}
}
