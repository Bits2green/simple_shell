#include "shell.h"

/**
* buffer_command_chain - buffers chained commands
* @info: parameter struct
* @cmd_buffer: address of command buffer
* @cmd_buffer_len: address of buffer length variable
*
* Return: bytes read
*/
ssize_t buffer_command_chain(info_t *info, char **cmd_buffer, size_t *cmd_buffer_len)
{
ssize_t bytes_read = 0;
size_t cmd_buffer_len_temp = 0;

if (!*cmd_buffer)
{
free(*cmd_buffer);
*cmd_buffer = NULL;
}

signal(SIGINT, block_ctrl_c);
bytes_read = input_line(cmd_buffer, &cmd_buffer_len_temp, stdin);

if (bytes_read > 0)
{
if ((*cmd_buffer)[bytes_read - 1] == '\n')
{
(*cmd_buffer)[bytes_read - 1] = '\0'; /* Remove trailing newline */
bytes_read--;
}

info->linecount_flag = 1;
remove_comments(*cmd_buffer);
build_shell_history_list(info, *cmd_buffer, info->shell_history_count++);
*cmd_buffer_len = bytes_read;

if (_strchr(*cmd_buffer, ';')) /* Is this a command chain? */
{
*cmd_buffer_len = bytes_read;
info->command_chain_buffer = cmd_buffer;
}
}

return (bytes_read);
}

/**
* get_input_line - gets an input line minus the newline
* @info: parameter struct
*
* Return: bytes read
*/
ssize_t get_input_line(info_t *info)
{
static char *command_buffer; /* The ';' command chain buffer */
static size_t cmd_buffer_iterator, cmd_buffer_index, cmd_buffer_len;
ssize_t bytes_read = 0;
char **command_buffer_ptr = &(info->arguments), *current_position;

_putchar(BUF_FLUSH);
bytes_read = buffer_command_chain(info, &command_buffer, &cmd_buffer_len);

if (bytes_read == -1) /* EOF */
return -1;

if (cmd_buffer_len)
{
cmd_buffer_index = cmd_buffer_iterator;
current_position = command_buffer + cmd_buffer_iterator;

check_command_chain(info, command_buffer, &cmd_buffer_index, cmd_buffer_iterator, cmd_buffer_len);

while (cmd_buffer_index < cmd_buffer_len)
{
if (is_command_chain(info, command_buffer, &cmd_buffer_index))
break;

cmd_buffer_index++;
}

cmd_buffer_iterator = cmd_buffer_index + 1;

if (cmd_buffer_iterator >= cmd_buffer_len) /* Reached the end of the buffer? */
{
cmd_buffer_iterator = cmd_buffer_len = 0; /* Reset position and length */
info->command_chain_type = CMD_NORMAL;
}

*command_buffer_ptr = current_position; /* Pass back a pointer to the current command position */
return (custom_strlen(current_position)); /* Return the length of the current command */
}

*command_buffer_ptr = command_buffer; /* Not a chain, pass back the buffer from input_line() */
return (bytes_read); /* Return the length of the buffer from input_line() */
}

/**
* read_buffer - reads a buffer
* @info: parameter struct
* @buffer: buffer
* @buffer_length: size
*
* Return: bytes read
*/
ssize_t read_buffer(info_t *info, char *buffer, size_t *buffer_length)
{
ssize_t bytes_read = 0;

if (*buffer_length)
return 0;

bytes_read = read(info->readfd, buffer, READ_BUF_SIZE);

if (bytes_read >= 0)
*buffer_length = bytes_read;

return (bytes_read);
}

/**
* input_line - gets the next line of input from STDIN
* @info: parameter struct
* @ptr: address of pointer to buffer, preallocated or NULL
* @length: size of preallocated ptr buffer if not NULL
*
* Return: bytes read
*/
int input_line(info_t *info, char **ptr, size_t *length)
{
static char buffer[READ_BUF_SIZE];
static size_t buffer_iterator, buffer_length;
size_t buffer_size;
ssize_t bytes_read, line_length;
char *position = NULL, *new_position = NULL, *current;

current = *ptr;
if (current && length)
line_length = *length;

if (buffer_iterator == buffer_length)
{
buffer_iterator = buffer_length = 0;
}

bytes_read = read_buffer(info, buffer, &buffer_length);

if (bytes_read == -1 || (bytes_read == 0 && buffer_length == 0))
return (-1);

position = _strchr(buffer + buffer_iterator, '\n');
buffer_size = position ? 1 + (size_t)(position - buffer) : buffer_length;

new_position = _realloc(current, line_length, line_length ? line_length + buffer_size : buffer_size + 1);

if (!new_position)
{
if (current)
free(current);

return -1;
}

if (line_length)
{
_strncat(new_position, buffer + buffer_iterator, buffer_size - buffer_iterator);
}
else
{
_strncpy(new_position, buffer + buffer_iterator, buffer_size - buffer_iterator + 1);
}

line_length += buffer_size - buffer_iterator;
buffer_iterator = buffer_size;
current = new_position;

if (length)
*length = line_length;

*ptr = current;
return line_length;
}

/**
* block_ctrl_c - blocks Ctrl-C signal
* @signal_number: the signal number
*
* Return: void
*/
void block_ctrl_c(__attribute__((unused)) int signal_number)
{
custom_puts("\n");
custom_puts("$ ");
custom_putchar(BUF_FLUSH);
}
