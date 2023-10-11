#include "shell.h"

int main(int argc, char *argv[])
{
    char *input = NULL;
    size_t input_size = 0;
    ssize_t read_size;
    struct Command command;
    int i;

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
        parse_input(input, &command);

        /*Debug: Print the parsed command*/
        my_printf("Command: %s\n", command.name);
        for (i = 0; command.args[i] != NULL; i++) {
            my_printf("Arg %d: %s\n", i, command.args[i]);
        }

        /*Execute commands*/
        if (command.name != NULL) {
            if (strcmp(command.name, "cd") == 0) {
                /*Handle 'cd' as a built-in command*/
                if (chdir(command.args[0]) == -1) {
                    my_printf("Error: Failed to change directory\n");
                }
            } else {
                /*Execute external commands*/
                execute_command(&command);
            }
        }

        /*Handle built-in commands (e.g., "cd")*/

        /*Implement I/O redirection and pipes*/

        free(input); /*Free the dynamically allocated input buffer*/
    }

    return (0);
}
