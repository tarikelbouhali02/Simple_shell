#include "shell.h"

/**
 * tshell_interactive - UNIX command line interpreter
 *
 * Return: void
 */
void tshell_interactive(void)
{
char *line;
char **args;
int status = -1;
do {
	printf("simple_prompt$ ");
	line = rread_line();
	args = ssplit_line(line);
	status = texecute_args(args);
	free(line);
	free(args);
if (status>= 0) 
{
	exit(status);
}
} while (status == -1);
}
