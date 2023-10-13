#include "shell.h"

/*Exit the shell*/
void exit_shell() {
    my_printf("Exiting the shell.\n");
    exit(0);
}

/*Print the current environment variables*/
void print_environment(char **envp) {
    for (int i = 0; envp[i] != NULL; i++) {
        my_printf("%s\n", envp[i]);
    }
}


