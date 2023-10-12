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

pid_t current_child_pid;

/* ++++++++++++++++ Functions ++++++++++++++++++++++*/

/*mv_print.c*/
void my_printf(const char *format, ...);

/* Tokenizer.c */
void parse_input(char *input, struct Command *command);

/*Excecute_cmd.c*/
int execute_command(struct Command *command);

/*Sigint_handler.c*/
void sigint_handler(int signum);

/*Sigtstp_handler.c*/
void sigtstp_handler(int signum);



#endif