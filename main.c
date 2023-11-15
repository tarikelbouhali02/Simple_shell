#include "shell.h"

/**
 * main - function that checks shell is called
 *
 * Return: 0 on success
 */
int main(void)
{
if (isatty(STDIN_FILENO) == 1)
{
	tshell_interactive();
}
else
{
	tshell_no_interactive();
}
return (0);
}
