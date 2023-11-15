//tshell_no_interactive.c
#include "shell.h"

/**
 * tshell_no_interactive - unix command line interpreter
 *
 * Return: void
 */
void tshell_no_interactive(void)
{
 char *line;
 char **args;
 int status = -1;

do {
  line = rread_stream();
  args = ssplit_line(line); /* tokenize line */
  status = texecute_args(args);
  /* avoid memory leaks */
  free(line);
  free(args);
  /* exit with status */
  if (status >= 0)
  {
   exit(status);
  }
 } while (status == -1);
}
