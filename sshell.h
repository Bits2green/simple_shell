#ifndef SSHELL_H
#define SSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

#define DELIM " \t\n"

extern char **environ;

/*_tokenizer.c*/
char **tokenize(char *line);

/*_execute.c*/
int _run(char **cmd, char **argv, int index);
char *readLine(void);
void free_string_array(char **array);

/*_strings.c*/
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strdup(const char *str);

/*_getenv.c*/
char *_getenv(char *var);

/*_getpath.c*/
char *_getpath(char *cmd);

/*_utils.c*/
void _perror(char *name, char *cmd, int index);
char *_atoi(int n);
void reverse_string(char *str, int len);

/*_builtin.c*/
void _display_env(char **cmd, int *status);
void _quit_shell(char **cmd, int *status);
void _handle_b(char **cmd, char **argv, int *status, int index);
int _builtin_s(char *cmd);



#endif
