#include "shell.h"

/**
 * t_build_dynamic_environ - Builds the "env vars" array using dynamic memory
*/
void t_build_dynamic_environ(void)
{
	int count_envs = 0;
	char **new_environ;

	while (__environ[count_envs] != NULL)
		count_envs++;

	new_environ = allocate_memory(sizeof(char *) * (count_envs + 1));
	for (count_envs = 0;  __environ[count_envs] != NULL; count_envs++)
		new_environ[count_envs] = duplicate_string(__environ[count_envs]);

	/* Last element should be NULL */
	new_environ[count_envs] = NULL;
	/* Asign new memory dynamically allocated */
	__environ = new_environ;
}

/**
 * t_free_dynamic_environ - Frees the memory allocated to hold "env vars"
 */
void t_free_dynamic_environ(void)
{
	t_free_dbl_ptr(__environ);
}
