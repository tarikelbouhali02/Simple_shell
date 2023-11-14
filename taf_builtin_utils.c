#include "shell.h"

/**
 * tavalidate_env_name - Validates at in  env var name
 * @name: String to the validated
 *
 * Return: zero, on success, minus one on error
*/
int tavalidate_env_name(char *name)
{
	if (name == NULL)
	{
		taprint_builtin_error("setenv: Needs 2 args", "");
		return (-1);
	}

	if (!tais_valid_env_var_name(name))
	{
		taprint_builtin_error("setenv: Invalid name ", name);
		return (-1);
	}

	return (0);
}

/**
 * tais_valid_env_var_name - Checks  the env name is valid
 * @name: String to be checked
 *
 * Return: one  if is valid, zero otherwise
*/
int tais_valid_env_var_name(char *name)
{
	int t;
	/* Verify that name it is valid taenv_var name (without "=") */
	for (t = 0; name[t] != '\0'; t++)
		if (name[t] == '=')
			return (0);

	return (1);
}

/**
 * taget_env_index - Check in env variable exists and returns the index
 * @name: Name to be searched
 *
 * Return: Index of the env var, minus one on error
*/
int taget_env_index(char *name)
{
	int t;
	int len = ta_strlen(name);

	for (t = 0; __tenviron[t] != NULL; t++)
		if (ta_strncmp(__tenviron[t], name, len) == 0)
			return (t);

	return (-1);
}
