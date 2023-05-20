#include "simple_shell.h"

/**
 * main - The entry point for the simple shell program
 * @argc: The number of command line arguments
 * @argv: An array of command line argument strings
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv)
{
	char cmd[MAX_CMD_LENGTH];

	while (1)
	{
		printf("simple_shell$");
		if (fgets(cmd, MAX_CMD_LENGTH, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		/*Remove trailing newline character*/
		cmd[strcspn(cmd, "\n")] = '\0';

		/*Check for built-in commands*/
		if (strcmp(cmd, "cd") == 0)
		{
			/*Handle cd command*/
			handle_cd_command();
			continue;
		} else if (strcmp(cmd, "exit") == 0)
		{
		/*Handle exit command*/
			handle_exit_command();
			continue;
		} else if (strcmp(cmd, "env") == 0)
		{
			/*Handle env command*/
			handle_env_command();
			continue;
		}

		/*Execute command*/
		if (!execute_command(cmd))
		{
			continue;
		}
	}
	return (0);
}
