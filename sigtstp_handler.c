#include "shell.h"

void sigtstp_handler(int signum) {
    (void)signum;
    if (current_child_pid > 0) {
        /*Suspend the currently running command*/
        kill(current_child_pid, SIGSTOP);
        my_printf("Command suspended. Press 'fg' to resume.\n");
    }
}