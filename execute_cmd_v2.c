#include "shell.h"


/*Custom function to execute a command using the PATH*/
int execute_command_with_path(struct Command *command, char **envp) {

    pid_t current_child_pid;
    char *token;
    char *path = custom_getenv("PATH", envp);

    if (path == NULL) {
        my_printf("PATH environment variable not set.\n");
        return -1;
    }

    /*Tokenize the PATH value based on ':'*/
    token = strtok(path, ":");

    while (token != NULL) {
        char full_path[MAX_INPUT_SIZE]; /*Adjust the size as needed*/
        /*Form the full path to the executable*/
        my_snprintf(full_path, sizeof(full_path), "%s/%s", token, command->name);

        /*Check if the executable exists in the directory*/
        if (access(full_path, X_OK) == 0) {
            /*Execute the program*/
            current_child_pid = fork();
            if (current_child_pid == 0) {
                char *const args[] = {command->name, NULL};
                execve(full_path, args, envp);
                perror("execve failed");
                _exit(1);
            } else if (current_child_pid > 0) {
                int status;
                if (waitpid(current_child_pid, &status, 0) == -1) {
                    my_printf("./vcsh: Wait failed\n");
                }
                current_child_pid = 0; /*Reset the PID as the command has finished*/
            }
            return (0); /*Program found and executed, return success*/
        }

        token = strtok(NULL, ":");
    }

    my_printf("./vcsh: Command not found in PATH.\n");
    return (-1); /*Program not found*/
}
