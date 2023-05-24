#include "simple_shell.h"

void prompt_user(char *buffer)
{
	printf("simple_shell$ ");
	if (!fgets(buffer, BUFFER_SIZE, stdin))
	{
		exit(EXIT_SUCCESS);
	}
	buffer[strcspn(buffer, "\n")] = '\0';
}
