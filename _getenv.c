#include "shell.h"

/*Function to get the value of an environment variable from a given environment variable list*/
char *custom_getenv(const char *var_name, char **envp) {
    int i;

    for (i = 0; envp[i] != NULL; i++) {
        /*Environment variables are typically in the form "NAME=VALUE"*/
        if (strncmp(envp[i], var_name, strlen(var_name)) == 0 && envp[i][strlen(var_name)] == '=') {
            /*Return the portion of the string after '=' as the value*/
            return envp[i] + strlen(var_name) + 1;
        }
    }
    return NULL; /*Variable not found*/
}
