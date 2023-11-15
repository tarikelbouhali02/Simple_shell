#include "shell.h"

static int EXIT_CODE;
static int no_init_exit_code = 1;

/**
 * process_exit_code - Returns the address at  EXIT_CODE is stored
 *
 * Return: Address of EXIT_CODE var
*/
int *tafprocess_exit_code()
{
	if (no_init_exit_code)
	{
		EXIT_CODE = 0;
		no_init_exit_code = 0;
	}

	return (&EXIT_CODE);
}

/**
 * set_process_exit_code - Sets  value for EXIT_CODE var
 * @code: Number representing exit code
*/
void tafset_process_exit_code(int code)
{
	EXIT_CODE = code;
}
