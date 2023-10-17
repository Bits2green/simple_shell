#ifndef _SHELL_H_
#define _SHELL_H_

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define SHELL_HIST_FILE ".simple_shell_history"
#define SHELL_HIST_MAX 4096

#define INFO_INIT                                                               \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}


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

#define COMMAND_NORM 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

#define USE_GETLINE 0

/*list_t*/
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/*command*/
typedef struct builtin
{
	char *command;
	int (*function)(info_t *);
} builtin_table;

/*info_t*/
typedef struct info_t
{
	char *arg;
	char **command_argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *environment;
	list_t *shell_history;
	list_t *alias;
	char **custom_environ;
	int env_changed;
	int status;
	char **command_chain_buffer;	  /* pointer to cmd ; chain buffer, for memory mangement */
	int command_chain_type; /* CMD_type ||, &&, ; */
	int readfd;
	int shell_history_count;
} info_t;

/*loosmsh.c*/
int run_shell(info_t *info, char **av);
int find_builtin_command(info_t *info);
void find_executable_command(info_t *info);
void execute_command(info_t *info);

/*_parse_input.c*/
int is_executable(info_t *info, char *path);
char *copy_chars(char *src, int start, int stop);
char *find_executable_path(info_t *info, char *path_str, char *command);

/*print_helpers.c*/
void custom_eputs(char *str);
int custom_eputchar(char c);
int custom_putfd(char c, int fd);
int custom_putsfd(char *str, int fd);

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

/*tokenize_input.c*/
char **split_string(char *str, char *delimiters);
char **split_string2(char *str, char delimiter);

/*reallocate_helper.c*/
char *custom_memset(char *s, char b, unsigned int n);
void custom_ffree(char **pp);
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/*free.c*/
int custom_free(void **ptr);

/*strtoi.c*/
int is_shell_interactive(info_t *info);
int is_character_delimiter(char c, char *delimiters);
int is_alphabetic(int c);
int string_to_integer(char *s);

/*more_print_helpers.c*/
int custom_erratoi(char *s);
void custom_print_error(info_t *info, char *estr);
int custom_print_d(int input, int fd);
char *custom_convert_number(long int num, int base, int flags);
void custom_remove_comments(char *buf);

/*builtins1.c*/
int my_exit(info_t *info);
int my_cd(info_t *info);
int my_help(info_t *info);

/*builtins2.c*/
int my_history(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int my_alias(info_t *info);

/*readline.c*/
ssize_t buffer_command_chain(info_t *info, char **cmd_buffer, size_t *cmd_buffer_len);
ssize_t get_input_line(info_t *info);
ssize_t read_buffer(info_t *info, char *buffer, size_t *buffer_length);
int input_line(info_t *info, char **ptr, size_t *length);
void block_ctrl_c(__attribute__((unused)) int signal_number);

/*info.c*/
void custom_clear_info(info_t *info);
void custom_set_info(info_t *info, char **av);
void custom_free_info(info_t *info, int all);

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

/*shell_history.c*/
char *get_shell_history_file(info_t *info);
int write_shell_history(info_t *info);
int read_shell_history(info_t *info);
int build_shell_history_list(info_t *info, char *buffer, int line_count);
int renumber_shell_history(info_t *info);

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

/*helper_variables.c*/
int is_chain_delimiter(info_t *info, char *buffer, size_t *position);
void check_chain(info_t *info, char *buffer, size_t *position, size_t start, size_t length);
int replace_command_alias(info_t *info);
int replace_command_vars(info_t *info);
int replace_string(char **old_str, char *new_str);

#endif