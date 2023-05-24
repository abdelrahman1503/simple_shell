#include "simple_shell.h"

/**
 * interactive - returns ture if shell is interactive mode
 * @info: struct address
 *
 * Return 1 if interactivve mode, 0 otherwise
 */

int interactive(info_t *info)
{
	if (isatty(STDIN_FILENO))
	{
		return 1;
	}
	else
	{	
		return 0;

	}
}
