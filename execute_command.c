#include "simple_shell.h"

/**
 * execute_command - Executes the specified command
 * @cmd: The command to execute
 *
 * Return: 1 if the command was executed successfully, 0 otherwise
 */
int execute_command(char *cmd)
{
	char *path = getenv("PATH");
	char *dir;
	char full_path[MAX_CMD_LENGTH];
	char *args[MAX_ARGS];

	//Search for command in Path directories
	dir = strtok(path, ":");
	while (dir !=NULL){
		strcpy(full_path, dir );
		strcat(full_path, "/");
		strcat(full_path, cmd);
		if (access(full_path, F_OK) == 0){
			break;
		}
		dir = strtok(NULL, ":");
	}
	if (dir == NULL){
		fprintf(stderr, "Command not found: %s\n", cmd);
		return 0;
	}

	//Prase command line arguments
	int i = 0;

	char *token = strtok(cmd , " ");
	while (token != NULL && i < MAX_ARGS - 1){
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	//Execute command
	pid_t pid = fork();
	if (pid == -1){
	perror("fork");
	exit(EXIT_FAILURE);
	}else if (pid == 0){
	//Child process
	if (execv(full_path, args) == -1){
	perror("execv");
	exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
	}else{
	//Parrent process
	int status;
	if(waitpid(pid, &status, 0) == -1){
	perror("waitpid");
	exit(EXIT_FAILURE);
	}
	}
	return 1;
}	
