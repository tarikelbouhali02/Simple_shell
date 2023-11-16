#include "shell.h"

/**
 * tdispatch_error - Dispatches an error
 * @msg: Message to print as error
*/
void tdispatch_error(char *msg)
{
	/* int len =_tstrlen(msg); */
	perror(msg);
	/*write(STDERR_FILENO, msg, len);*/
	/*write(STDERR_FILENO,": not found\n", 12);*/
	exit(errno);
	/*exit(127); */
}

/**
 * print_tbuiltin_error - Prints error for buitin function
 * @msg: Error message
 * @arg: Argument passed to builtin
*/
void print_tbuiltin_error(char *msg, char *arg)
{
	int len =_tstrlen(msg);
	char *first_av = t_get_first_av();

	write(STDERR_FILENO, first_av,_tstrlen(first_av));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, msg, len);
	write(STDERR_FILENO, arg,_tstrlen(arg));
	write(STDERR_FILENO, "\n", 1);
	set_process_exit_code(2);
}
