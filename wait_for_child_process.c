#include "simple_shell.h"

void wait_for_child_process(pid_t pid, int *status)
{
	do
	{
		pid_t wpid = waitpid(pid, status, WUNTRACED);
		if (wpid == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
	} while (!WIFEXITED(*status) && !WIFSIGNALED(*status));
}
