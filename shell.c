#include "shell.h"

int main(int argc, char *argv[])
{
    char *input = NULL;
    size_t input_size = 0;
    ssize_t read_size;
    struct Command command;
    int i;

    /*Set up signal handlers*/ 
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);

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
                current_child_pid = fork(); /*Store the PID of the child process*/
                if (current_child_pid == 0) {
                    /*Child Process*/
                    execute_command(&command);
                } else if (current_child_pid > 0) {
                    /*Parent Process*/
                    int status;
                    if (waitpid(current_child_pid, &status, 0) == -1) {
                        my_printf("Error: Wait failed\n");
                    }
                    current_child_pid = 0; /*Reset the PID as the command has finished*/
                }
            }
        }

        /*Handle built-in commands (e.g., "cd")*/

        /*Implement I/O redirection and pipes*/

        if (input != NULL) { /*Check if memory is not already freed*/
            free(input); /*Free the dynamically allocated input buffer*/
            input = NULL; /*Set to NULL to avoid double freeing*/
        }
    }

    return (0);
}
