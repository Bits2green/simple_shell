#ifndef SHELL_H
#define SHELL_H

#define MAX_INPUT_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

/* Defining Structures */

struct Command {
    char *name;
    char *args[32]; /*Adjust the size as needed*/
};

/* ++++++++++++++++ Functions ++++++++++++++++++++++*/

/*mv_print.c*/
void my_printf(const char *format, ...);

/* _parse_input.c */
void parse_input(char *input, struct Command *command, char **envp);

/*excecute_cmd_v1.c*/
int execute_command(struct Command *command);

/*sigint_handler.c*/
void sigint_handler(int signum);

/*expandvars.c*/
void expand_env_vars(struct Command *command);

/*_getenv.c*/
char *custom_getenv(const char *var_name, char **envp);

/*execute_cmd_v2.c*/
int execute_command_with_path(struct Command *command, char **envp);

/*builtins.c*/
void exit_shell();
void print_environment(char **envp);

/*str_helpers.c*/
char *my_strdup(const char *str);
int my_strcmp(const char *s1, const char *s2);
size_t my_strlen(const char *str);
char *my_strcpy(char *dest, const char *src);

/*my_snprintf()*/
int my_snprintf(char *str, size_t size, const char *format, ...);

/*my_putint()*/
void my_putint(int num);

/*my_putchar()*/
void my_putchar(char c);

/*my_puts()*/
void my_puts(const char *str);


#endif
