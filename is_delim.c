#include "simple_shell.h"

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if ture, 0 if false
 */

int is_delim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
		{
			return 1;
		}
		delim++;
	}
	return 0;
}