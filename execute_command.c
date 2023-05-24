#include "simple_shell.h"

void execute_command(char **args)
{
	if (execve(args[0], args, environ) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}
