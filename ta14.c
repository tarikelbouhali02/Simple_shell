#include "shell.h"

/**
 * t_validate_env_name - Validates a env var name
 * @name: String to be validated
 *
 * Return: 0, on success, -1 on error
*/
int t_validate_env_name(char *name)
{
	if (name == NULL)
	{
		print_tbuiltin_error("setenv: Needs 2 args", "");
		return (-1);
	}

	if (!t_is_valid_env_var_name(name))
	{
		print_tbuiltin_error("setenv: Invalid name ", name);
		return (-1);
	}

	return (0);
}

/**
 * t_is_valid_env_var_name - Checks if the env name is valid
 * @name: String to be checked
 *
 * Return: 1 if is valid, 0 otherwise
*/
int t_is_valid_env_var_name(char *name)
{
	int i;
	/* Verify that name is a valid env_var name (without "=") */
	for (i = 0; name[i] != '\0'; i++)
		if (name[i] == '=')
			return (0);

	return (1);
}

/**
 * t_get_env_index - Check if a env variable exists and returns the index
 * @name: Name to be searched
 *
 * Return: Index of the env var, -1 on error
*/
int t_get_env_index(char *name)
{
	int i;
	int len =_tstrlen(name);

	for (i = 0; __environ[i] != NULL; i++)
		if (t_strncmp(__environ[i], name, len) == 0)
			return (i);

	return (-1);
}
