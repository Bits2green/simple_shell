#include "shell.h"

int main(int argc, char *argv[], char *envp[])
{
    char *input = NULL;
    size_t input_size = 0;
    ssize_t read_size;
    struct Command command;
    int i;
    int interactive = isatty(STDIN_FILENO);
    
    (void)argc, (void)argv;
    
    while (1) {
        if (interactive)
        {
            my_printf("smshell$ ");
            fflush(stdout); }
        read_size = getline(&input, &input_size, stdin);
        if (read_size == -1)
        {
            if (interactive)
                my_printf("\n");
            free(input);
            break; }
        parse_input(input, &command, envp);
        if (command.name != NULL)
        {
            if (my_strcmp(command.name, "cd") == 0)
            {
                if (chdir(command.args[0]) == -1)
                    my_printf("./vcsh: Failed to change directory\n"); }
            else if (my_strcmp(command.name, "exit") == 0)
                exit_shell();
            else if (my_strcmp(command.name, "env") == 0)
                print_environment(envp);
            else 
            {
                if (execute_command_with_path(&command, envp) == -1)
                    my_printf("./vcsh: Command not found.\n"); } }
        if (input != NULL)
        {
            free(input);
            input = NULL; }
        if (command.name != NULL)
        {
            free(command.name);
            for (i = 0; command.args[i] != NULL; i++)
                free(command.args[i]);
            memset(&command, 0, sizeof(struct Command)); } }
    return (0); }
