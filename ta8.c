#include "shell.h"

/**
 * _handle_enter - Check if no command was entered
 * @commands: String of commnands
 *
 * Return: 1 if no command was entered(just spaces and ENTER), 0 otherwise
*/
int _handle_enter(char **commands)
{
	if (commands[0] == NULL || _strcmp(commands[0], "\n") == 0)
		return (1);

	return (0);
}
