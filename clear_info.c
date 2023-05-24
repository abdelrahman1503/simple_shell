#include "simple_shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
void clear_info(st_info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
