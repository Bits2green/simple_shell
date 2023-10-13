#include "shell.h"

/**
 * parse_input - parses the command provided by the user
 * @input: the command
 * @Command: Structure to handle the input
 * @envp: provides the PATH to the executable in the /bin folder
 * 
 * Return: 0
*/

void parse_input(char *input, struct Command *command, char **envp) {

    int i;
    char *token;
    int arg_index = 0;
    int is_command_name_set;

    /*Initialize the command's arguments*/
    for (i = 0; i < sizeof(command->args) / sizeof(command->args[0]); i++) {
        command->args[i] = NULL;
    }

    /*Tokenize the input to separate the command name and its arguments*/
    token = strtok(input, " \t\n"); /*Tokenize based on space, tab, and newline*/

    /*Initialize the argument index*/
    arg_index = 0;
    
    /*Initialize a flag to determine if we've encountered the command name*/
    is_command_name_set = 0;

    while (token != NULL) {
        if (!is_command_name_set) {
            /*The first token is the command name*/
            command->name = my_strdup(token);
            is_command_name_set = 1;
        } else {
            /*Subsequent tokens are arguments*/
            /*Expand environment variables in arguments*/
            if (token[0] == '$') {
                char *var_name = token + 1; /*Skip the '$'*/
                char *var_value = custom_getenv(var_name, envp);
                if (var_value != NULL) {
                    /*Replace the argument with the environment variable value*/
                    command->args[arg_index] = my_strdup(var_value);
                } else {
                    /*Environment variable not found, keep the original argument*/
                    command->args[arg_index] = my_strdup(token);
                }
            } else {
                /*Not an environment variable, keep the original argument*/
                command->args[arg_index] = my_strdup(token);
            }

            /*Move to the next argument*/
            arg_index++;
        }

        /*Get the next token*/
        token = strtok(NULL, " \t\n");
    }
}
