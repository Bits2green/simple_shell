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

/*even_more_string_helpers.c*/
char *custom_strncpy(char *dest, char *src, int n);
char *custom_strncat(char *dest, char *src, int n);
char *custom_strchr(char *s, char c);

/*reallocate_helper.c*/
char *custom_memset(char *s, char b, unsigned int n);
void custom_ffree(char **pp);
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/*info.c*/
void custom_clear_info(info_t *info);
void custom_set_info(info_t *info, char **av);
void custom_free_info(info_t *info, int all);

/*lists_helper.c*/
list_t *add_node_at_start(list_t **head, const char *data, int index);
list_t *add_node_at_end(list_t **head, const char *data, int index);
size_t print_list_strings(const list_t *head);
int delete_node_by_index(list_t **head, unsigned int index);
void free_string_list(list_t **head_ptr);

/*more_lists_helpers.c*/
size_t linked_list_length(const list_t *head);
char **linked_list_to_strings(list_t *head);
size_t print_linked_list(const list_t *head);
list_t *find_node_starts_with(list_t *head, char *prefix, char next_char);
ssize_t get_node_index_in_list(list_t *head, list_t *node);

/*env.c*/
int print_custom_env(info_t *info);
char *get_custom_env_value(info_t *info, const char *name);
int set_custom_env_var(info_t *info);
int unset_custom_env_var(info_t *info);
int populate_custom_env_list(info_t *info);

/*_getenv.c*/
char **copy_environ(info_t *info);
int custom_unset_env_var(info_t *info, char *var);
int custom_set_env_var(info_t *info, char *var, char *value);

/*_parse_input.c*/
int is_executable(info_t *info, char *path);
char *copy_chars(char *src, int start, int stop);
char *find_executable_path(info_t *info, char *path_str, char *command);

/*free.c*/
int custom_free(void **ptr);

#endif