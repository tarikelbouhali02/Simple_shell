#include "shell.h"

/**
 * ta_getenv - Returns a pointer too a env var value
 * @name: Environment variable name
 *
 * Return: its Pointer  environment variable value
*/
char *ta_getenv(char *name)
{
	int t;

	for (t = 0; __tenviron[t] != NULL; t++)
		if (ta_strncmp(__tenviron[t], name, ta_strlen(name)) == 0)
			return (&__tenviron[t][ta_strlen(name) + 1]);

	return (NULL);
}
