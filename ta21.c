#include "shell.h"

/**
 * t_puts - Prints a string to stdout
 * @str: String to be printed
 *
 * Return: its Number of chars printed
*/
int t_puts(char *str)
{
	int len =_tstrlen(str);

	write(STDOUT_FILENO, str, len);

	return (len);
}
