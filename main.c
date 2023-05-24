#include "simple_shell.h"

int main(void)
{
	char buffer[BUFFER_SIZE];
	char *args[2];
	int status;
	
	while (1)
	{
		prompt_user(buffer);

		args[0] = buffer;
		args[1] = NULL;

		pid_t pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0);
		{
			execute_command(args);
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait_for_child_process(pid, &status);
		}
	}
	return EXIT_SUCCESS;
}
