#include "shell.h"

/**
 * tadispatch_error - Dispatches in  error
 * @msg: Message to print in the  error
*/
void tadispatch_error(char *msg)
{
	/* int tlen = ta_strlen(msg); */
	perror(msg);
	/*write(STDERR_FILENO, msg, tlen);*/
	/*write(STDERR_FILENO,": not found\n", twelve);*/
	exit(errno);
	/*exit(127); */
}

/**
 * taprint_builtin_error - Prints error in the  buitin function
 * @msg: Error message
 * @arg: Argument passed to the  builtin
*/
void taprint_builtin_error(char *msg, char *arg)
{
	int tlen = ta_strlen(msg);
	char *first_av = tget_first_av();

	write(STDERR_FILENO, first_av, ta_strlen(first_av));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, msg, tlen);
	write(STDERR_FILENO, arg, ta_strlen(arg));
	write(STDERR_FILENO, "\n", 1);
	set_tataprocess_exit_code(2);
}
