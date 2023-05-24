#include "simple_shell.h"
#include <string.h>
#include <stdlib.h>

extern char **environ;

void run_shell(void)
{
    pid_t child_pid;
    int status;
    char *command;
    size_t command_size = 0;

    while (1)
    {
        printf("$ ");
        fflush(stdout);

        command = NULL;
        if (getline(&command, &command_size, stdin) == -1)
        {
            printf("\n");
            free(command);
            exit(EXIT_SUCCESS);
        }

        /* Remove newline character from command */
        command[strcspn(command, "\n")] = '\0';

        child_pid = fork();
        if (child_pid == -1)
        {
            perror("Error creating child process");
            exit(EXIT_FAILURE);
        }
        if (child_pid == 0)
        {
            /* Child process */
            char **argv = malloc(sizeof(char *) * 2);
            argv[0] = command;
            argv[1] = NULL;
            if (execve(command, argv, environ) == -1)
            {
                perror("Error executing command");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process */
            waitpid(child_pid, &status, 0);
        }

        free(command);
    }
}
