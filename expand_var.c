#include "shell.h"

/*Function to expand environment variables in command arguments*/
void expand_env_vars(struct Command *command) {
    for (int i = 0; command->args[i] != NULL; i++) {
        if (command->args[i][0] == '$') {
            /*The argument appears to be an environment variable*/
            char *var_name = command->args[i] + 1; /*Skip the '$'*/
            char *var_value = getenv(var_name);
            if (var_value != NULL) {
                /*Replace the argument with the environment variable value*/
                free(command->args[i]);
                command->args[i] = strdup(var_value);
            }
        }
    }
}
