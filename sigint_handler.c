#include "shell.h"

void sigint_handler(int signum) {
    pid_t current_child_pid;

    (void)signum;
    if (current_child_pid > 0) {
        /*Terminate the currently running command*/
        kill(current_child_pid, SIGKILL);
        my_printf("Command terminated.\n");
    }
}