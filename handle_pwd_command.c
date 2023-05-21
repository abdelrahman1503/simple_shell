#include "simple_shell.h"

/**
 * handle_pwd_command - Handles the pwd command
 */
void handle_pwd_command(void)
{
	char cwd[MAX_CMD_LENGTH];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return;
	}
	printf("%s\n", cwd);
}
