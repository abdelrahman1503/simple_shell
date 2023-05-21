#include "simple_shell.h"

/**
 * handle_cd_command - Handles the cd command
 */
void handle_cd_command(void)
{
	if (chdir(getenv("HOME")) == -1)
	{
		perror("chdir");
	}
}
