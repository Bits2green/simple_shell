#include "shell.h"

void parse_input(char *input, struct Command *command) {
    char *token;
    int arg_index = 0;
    int i;

    /*Initialize the command structure*/
    command->name = NULL;
    for (i = 0; i < 32; i++) {
        command->args[i] = NULL;
    }

    /*Tokenize the input*/
    token = strtok(input, " \t\n");
    while (token != NULL) {
        if (command->name == NULL) {
            command->name = strdup(token);
        } else {
            command->args[arg_index] = strdup(token);
            arg_index++;
        }

        token = strtok(NULL, " \t\n");
    }
}