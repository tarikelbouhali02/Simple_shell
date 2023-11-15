#include "shell.h"

/**
 * ta_puts - Prints  string the stdout
 * @str: its String the be printed
 *
 * Return: Number at chars printed
*/
int ta_puts(char *str)
{
	int tlen = ta_strlen(str);

	write(STDOUT_FILENO, str, tlen);

	return (tlen);
}
