#include "shell.h"

/**
 * tahandle_enter - Check else if no command was entered
 * @commands: String in commnands
 *
 * Return: one  if no command was entered(just spaces and ENTER), zero otherwise
*/
int tahandle_enter(char **commands)
{
	if (commands[0] == NULL || ta_strcmp(commands[0], "\n") == 0)
		return (1);

	return (0);
}
