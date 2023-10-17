#include "shell.h"

/**
* main - Entry point of the shell
* @argc: Argument count
* @argv: Argument vector
*
* Return: 0 on success, 1 on error
*/
int main(int argc, char **argv)
{
info_t shell_info[] = { INFO_INIT };
int read_fd = 2;

asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (read_fd)
: "r" (read_fd));

if (argc == 2)
{
read_fd = open(argv[1], O_RDONLY);
if (read_fd == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
_eputs(argv[0]);
_eputs(": 0: Can't open ");
_eputs(argv[1]);
_eputchar('\n');
_eputchar(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
shell_info->readfd = read_fd;
}
populate_custom_env_list(shell_info);
read_shell_history(shell_info);
run_shell(shell_info, argv);
return (EXIT_SUCCESS);
}
