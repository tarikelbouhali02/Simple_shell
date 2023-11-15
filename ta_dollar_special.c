#include "shell.h"

static int tEXIT_CODE;
static int tno_init_exit_code = 1;

/**
 * taprocess_exit_code - Returns the address  which tEXIT_CODE is stored
 *
 * Return: Address  tEXIT_CODE var
*/
int *taprocess_exit_code()
{
	if (tno_init_exit_code)
	{
		tEXIT_CODE = 0;
		tno_init_exit_code = 0;
	}

	return (&tEXIT_CODE);
}

/**
 * taset_process_exit_code - Sets the value fr tEXIT_CODE var
 * @code:its  Number representing ext code
*/
void taset_process_exit_code(int code)
{
	tEXIT_CODE = code;
}
