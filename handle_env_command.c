#include "simple_shell.h"

/* Declare the environ variable as an external variable */
extern char **environ;

/**
 * handle_env_command - Handles the env command
 */
void handle_env_command(void)
{
	char **env = environ;
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
