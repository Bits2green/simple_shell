#include "sshell.h"

/**
 * main - 
 * @ac:
 * @av:
 * Return:
*/

int main(int ac, char **argv)
{
    char *line = NULL;
    /*char **cmd = NULL;*/
    int status = 0;
    (void)ac; (void)argv;

    while (1)
    {
        line = readLine();
        if (line == NULL) /*EOF or ctrlD*/
        {
            write(STDOUT_FILENO, "\n ", 1);
            return (status);
        }

        printf("%s\n", line);
        free(line);
        /*cmd = tokenize(line);

        status = _run(cmd, argv);*/
    }
}
