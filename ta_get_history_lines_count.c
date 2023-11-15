#include "shell.h"

static int COUNT_LINES;

/**
 * taupdate_count_lines - Counts the lines at a previo
*/
void taupdate_count_lines(void)
{
	char tcurr_dir[512];
	char tread_buff[1024];
	int t, fd, tchars_read;
	char *thome;

	COUNT_LINES = 0;

	if (getcwd(tcurr_dir, 512) == NULL)
		return;

	thome = ta_getenv("HOME");
	if (thome == NULL)
		thome = "";

	if (chdir(thome) == -1)
		return;

	fd = open(".simple_shell_history", O_RDONLY);
	if (fd == -1)
		return;

	while ((tchars_read = read(fd, tread_buff, 1024)) != -1)
	{
		if (tchars_read == 0)
			break;

		for (t = 0; t < tchars_read; t++)
			if (tread_buff[t] == '\n')
				COUNT_LINES++;
	}

	chdir(tcurr_dir);
}

/**
 * taget_history_lines_count - Returns the lines count in history file
 *
 * Return:its  Pointer to lines count
*/
int *taget_history_lines_count()
{
	return (&COUNT_LINES);
}
