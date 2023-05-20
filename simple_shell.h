#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 32

/* Function decleration */
int execute_command(char *cmd);
void handle _cd_command(void);
void handle_exit_command(void);
void handle_env_command(void);
void handle_pwd_command(void);
#endif /*SIMPLE_SHELL_H*/
