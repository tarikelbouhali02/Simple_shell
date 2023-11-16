#include "shell.h"

static int COUNT_LINES;

/**
 * t_update_count_lines - Counts the lines in a previo
*/
void t_update_count_lines(void)
{
	char curr_dir[512];
	char read_buff[1024];
	int i, fd, chars_read;
	char *home;

	COUNT_LINES = 0;

	if (getcwd(curr_dir, 512) == NULL)
		return;

	home = t_getenv("HOME");
	if (home == NULL)
		home = "";

	if (chdir(home) == -1)
		return;

	fd = open(".simple_shell_history", O_RDONLY);
	if (fd == -1)
		return;

	while ((chars_read = read(fd, read_buff, 1024)) != -1)
	{
		if (chars_read == 0)
			break;

		for (i = 0; i < chars_read; i++)
			if (read_buff[i] == '\n')
				COUNT_LINES++;
	}

	chdir(curr_dir);
}

/**
 * t_get_history_lines_count - Returns the lines count of history file
 *
 * Return: its Pointer to lines count
*/
int *t_get_history_lines_count()
{
	return (&COUNT_LINES);
}
