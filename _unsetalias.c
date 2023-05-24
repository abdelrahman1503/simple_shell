#include "simple_shell.h"

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(st_info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}