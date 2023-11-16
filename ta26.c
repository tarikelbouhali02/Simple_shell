#include "shell.h"

/**
 * t_getenv - Returns a pointer to a env var value
 * @name: Environment variable name
 *
 * Return: its Pointer to environment variable value
*/
char *t_getenv(char *name)
{
	int i;

	for (i = 0; __environ[i] != NULL; i++)
		if (t_strncmp(__environ[i], name,_tstrlen(name)) == 0)
			return (&__environ[i][_strlen(name) + 1]);

	return (NULL);
}
