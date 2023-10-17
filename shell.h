#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/*print_helpers.c*/
void custom_eputs(char *str);
int custom_eputchar(char c);
int custom_putfd(char c, int fd);
int custom_putsfd(char *str, int fd);

/*more_print_helpers.c*/
int custom_erratoi(char *s);
void custom_print_error(info_t *info, char *estr);
int custom_print_d(int input, int fd);
char *custom_convert_number(long int num, int base, int flags);
void custom_remove_comments(char *buf);

/*string_helpers.c*/
int custom_strlen(char *str);
int custom_strcmp(char *str1, char *str2);
char *custom_starts_with(const char *str, const char *prefix);
char *custom_strcat(char *destination, char *source);

/*more_string_helpers.c*/
char *custom_strcpy(char *dest, char *src);
char *custom_strdup(const char *str);
void custom_puts(char *str);
int custom_putchar(char c);

/*reallocate_helper.c*/
char *custom_memset(char *s, char b, unsigned int n);
void custom_ffree(char **pp);
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size);



#endif