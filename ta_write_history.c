#include "shell.h"

/**
 * tawrite_history - will  Writes  to the history to the  a file in thome dir
*/
void tawrite_history(void)
{
	list_t *tcurr;
	int fd;
	char *thome;

	thome = ta_getenv("HOME");
	if (thome == NULL)
		thome = "/";

	if (chdir(thome) == -1)
		return;

	fd = open(".simple_shell_history", O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd == -1)
		return;

	for (tcurr = *get_history_addrss(); tcurr != NULL; tcurr = tcurr->next)
	{
		write(fd, tcurr->str, tcurr->len);
		write(fd, "\n", 1);
	}

	close(fd);
}
