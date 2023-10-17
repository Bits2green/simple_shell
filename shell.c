#include "shell.h"

int main(int argc, char *argv[], char *envp[])
{
char *input = NULL;
size_t input_size = 0;
ssize_t read_size;
struct Command command;
int i;
int interactive = isatty(STDIN_FILENO); /*Check if running interactively*/

/*Set up signal handler*/
/*signal(SIGINT, sigint_handler);*/

(void)argc, (void)argv;

while (1) {
if (interactive) {
my_printf("smshell$ ");
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
parse_input(input, &command, envp);

/*Execute commands*/
if (command.name != NULL) {
/*Expand environment variables in command arguments*/
parse_input(input, &command, envp);

if (my_strcmp(command.name, "cd") == 0) {
/*Handle 'cd' as a built-in command*/
if (chdir(command.args[0]) == -1) {
my_printf("./vcsh: Failed to change directory\n");
}
} else if (my_strcmp(command.name, "exit") == 0) {
/*Handle 'exit' as a built-in command to exit the shell*/
exit_shell();
} else if (my_strcmp(command.name, "env") == 0) {
/*Handle 'env' as a built-in command to print environment variables*/
print_environment(envp);
} else {
/*Execute external commands using the PATH*/
if(execute_command_with_path(&command, envp) == -1) {
/*Command not found in PATH*/
my_printf("./vcsh: Command not found.\n");
}
}
}
/*Handle built-in commands (e.g., "cd")*/
if (input != NULL) { /*Check if memory is not already freed*/
free(input); /*Free the dynamically allocated input buffer*/
input = NULL; /*Set to NULL to avoid double freeing*/
}

/*Free dynamically allocated memory in the command struct*/
if (command.name != NULL) {
free(command.name);
for (i = 0; command.args[i] != NULL; i++) {
free(command.args[i]);
}
/*Reset the command struct*/
memset(&command, 0, sizeof(struct Command));
}
}
return (0);
}
