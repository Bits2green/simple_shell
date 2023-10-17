#ifndef SHELL_H
#define SHELL_H

#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <signal.h>

int compare_strings(char *str1, char *str2);
int write_char(char ch);
void print_string(char *str);
int string_length(char *str);
char *concatenate_strings(char *s1, char *s2);

/*helper_funcs1.c*/
int startsWithSlash(char *input);
int isExitCommand(char *userInput, char *exitCommand);
int isEnvCommand(char *userInput, char *envCommand);
char **parseInput(char *input);
void controlD(int signal);

/*shell_prompt.c*/
void runShell(void);

void executeCommand(char **command);

char *findExecutablePath(char *command);


#endif