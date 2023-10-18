#include "sshell.h"

/**
 * main - 
 * @ac:
 * @av:
 * Return:
*/

int main(int ac, char **argv)
{
    char *line = NULL; **cmd = NULL;
    int status = 0;
    (void)ac; (void)argv;

    while (1)
    {
        line = readLine();
        if (line == NULL) /*EOF or ctrlD*/
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n ", 1);
            return (status);
        }

        free(line);
        cmd = tokenize(line);

        /*status = _run(cmd, argv);*/
    }
}
