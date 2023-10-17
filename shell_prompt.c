#include "shell.h"

/**
* runShell - Run the shell.
*/
void runShell(void)
{
for (;;)
{
char *inputLine = NULL, **environment;
pid_t childPid;
int childStatus, bytesRead;
size_t bufferSize = 0;

print_string("vmshell$ ");
bytesRead = getline(&inputLine, &bufferSize, stdin);
if (bytesRead == -1)
exit(98);
if (isExitCommand(inputLine, "exit") == 0)
exit(0);
if (isEnvCommand(inputLine, "env") == 0)
{
while (*environment != NULL)
{
if (!compare_strings(*environment, "USER") ||
!compare_strings(*environment, "LANGUAGE") ||
!compare_strings(*environment, "SESSION") ||
!compare_strings(*environment, "COMPIZ_CONFIG_PROFILE") ||
!compare_strings(*environment, "SHLV") ||
!compare_strings(*environment, "HOME") ||
!compare_strings(*environment, "C_IS") ||
!compare_strings(*environment, "DESKTOP_SESSION") ||
!compare_strings(*environment, "LOGNAME") ||
!compare_strings(*environment, "TERM") ||
!compare_strings(*environment, "PATH"))
{
print_string(*environment);
print_string("\n");
}
environment++;
}
}
childPid = fork();
if (childPid < 0)
perror("Error");
if (childPid == 0)
parseInput(inputLine);
else
wait(&childStatus);
}
}
