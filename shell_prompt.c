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
                if (!startsWithSlash(*environment, "USER") ||
                    !startsWithSlash(*environment, "LANGUAGE") ||
                    !startsWithSlash(*environment, "SESSION") ||
                    !startsWithSlash(*environment, "COMPIZ_CONFIG_PROFILE") ||
                    !startsWithSlash(*environment, "SHLV") ||
                    !startsWithSlash(*environment, "HOME") ||
                    !startsWithSlash(*environment, "C_IS") ||
                    !startsWithSlash(*environment, "DESKTOP_SESSION") ||
                    !startsWithSlash(*environment, "LOGNAME") ||
                    !startsWithSlash(*environment, "TERM") ||
                    !startsWithSlash(*environment, "PATH"))
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
