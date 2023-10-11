#include "shell.h"

int execute_command(struct Command *command) {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        my_printf("Error: Fork failed\n");
        return (-1);
    } else if (child_pid == 0) {
        /*Child process*/
        if (execve(command->name, command->args, NULL) == -1) {
            my_printf("Error: Command not found\n");
            _exit(EXIT_FAILURE);
        }
    } else {
        /*Parent process*/
        int status;
        if (wait(&status) == -1) {
            my_printf("Error: Wait failed\n");
            return (-1);
        }
    }

    return (0);
}