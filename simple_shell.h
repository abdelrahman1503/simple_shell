#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
/* Function decleration */
void prompt_user(char *buffer);
void execute_command(char **args);
void wait_for_child_process (pid_t pid, int *status);

#endif /* SIMPLE_SHELL_H */
