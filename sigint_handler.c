#include "shell.h"

void sigint_handler(int signum) {
    my_printf("Received SIGINT (Ctrl+C). Command terminated.\n");
}