#include "simple_shell.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

extern char **environ;

void run_shell(void)
{
    pid_t child_pid;
    int status;
    char *command;

    while (1)
    {
        char *cwd = getcwd(NULL, 0);
        char *prompt = malloc(strlen(cwd) + 10);
        sprintf(prompt, "%s# ", cwd);
        free(cwd);

        command = readline(prompt);
        free(prompt);

        if (command == NULL)
        {
            printf("\n");
            exit(EXIT_SUCCESS);
        }

        if (strlen(command) == 0)
        {
            free(command);
            continue;
        }

        add_history(command);

        child_pid = fork();
        if (child_pid == -1)
        {
            perror("Error creating child process");
            exit(EXIT_FAILURE);
        }
        if (child_pid == 0)
        {
            /* Child process */
            char **argv = malloc(sizeof(char *) * 3);
            argv[0] = strtok(command, " ");
            argv[1] = strtok(NULL, " ");
            argv[2] = NULL;
            if (execve(argv[0], argv, environ) == -1)
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
