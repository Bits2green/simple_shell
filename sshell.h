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

char **tokenize(char *line);

int _run(char **cmd, char **argv);
char *readLine(void);
void free_string_array(char **array);

/*strings.c*/
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strdup(const char *str);

char *_getenv(char *var);

#endif
