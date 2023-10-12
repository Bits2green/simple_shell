#include "shell.h"

void sigtstp_handler(int signum) {
    my_printf("Received SIGTSTP (Ctrl+Z). Command suspended.\n");
}