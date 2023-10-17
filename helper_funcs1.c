#include "shell.h"

/**
* startsWithSlash - Checks if a string starts with a slash.
* @input: Input string
* Return: 1 if it starts with a slash, 0 otherwise.
*/
int startsWithSlash(char *input)
{
int count = 0;

while (input[count])
{
if (input[0] == '/')
{
printf("%c\n", input[0]);
return (1);
}

count++;
}
return (0);
}

/**
* isExitCommand - Checks if the user entered the "exit" command.
* @userInput: User's input string
* @exitCommand: The "exit" command string
* Return: 1 if it's the "exit" command, 0 otherwise.
*/
int isExitCommand(char *userInput, char *exitCommand)
{
int index = 0;

for (; (*exitCommand != '\0' && *userInput != '\0')
&& *userInput == *exitCommand; userInput++)
{
if (index == 3)
break;
index++;
exitCommand++;
}

return (*userInput - *exitCommand);
}

/**
* isEnvCommand - Checks if the user entered the "env" command.
* @userInput: User's input string
* @envCommand: The "env" command string
* Return: 1 if it's the "env" command, 0 otherwise.
*/
int isEnvCommand(char *userInput, char *envCommand)
{
int index = 0;

for (; (*envCommand != '\0' && *userInput != '\0')
&& *userInput == *envCommand; userInput++)
{
if (index == 2)
break;
index++;
envCommand++;
}

return (*userInput - *envCommand);
}

/**
* parseInput - Identifies and splits the user's input string.
* @input: User's input string
* Return: Array of strings.
*/
char **parseInput(char *input)
{
char **tokens = malloc(1024 * sizeof(char *));
char *token;
int tokenIndex = 0;
char *delimiter = " \t\n";

token = strtok(input, delimiter);

while (token != NULL)
{
tokens[tokenIndex] = token;
tokenIndex++;
token = strtok(NULL, delimiter);
}
executeProcess(tokens);
return (tokens);
}

/**
* handleCtrlC - Prevents the shell from closing on Ctrl+C.
* @signal: Signal to handle
*/
void handleCtrlC(int signal)
{
(void) signal;
write(1, "\n$ ", 3);
}
