#include "shell.h"

int main(int argc, char *argv[])
{
    char *input = NULL;
    size_t input_size = 0;
    ssize_t read_size;

    int interactive = isatty(STDIN_FILENO); /*Check if running interactively*/

    (void)argc, (void)argv;

    while (1) {
        if (interactive) {
            my_printf("smshell ($) ");
            fflush(stdout);
        }

        read_size = getline(&input, &input_size, stdin);

        if (read_size == -1) {
            /* Handle Ctrl+D or input error */
            if (interactive) {
                my_printf("\n");
            }
            free(input);
            break;
        }

        /* Tokenize and parse input here*/

        /*Execute commands*/

        /*Handle built-in commands (e.g., "cd")*/

        /*Implement I/O redirection and pipes*/

        free(input); /*Free the dynamically allocated input buffer*/
    }

    return (0);
}
