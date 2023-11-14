#include "shell.h"

/**
 * tabuild_dynamic_environ - Builds the "env vars" array use dynamic memory
*/
void tabuild_dynamic_environ(void)
{
	int tcount_envs = 0;
	char **tnew_environ;

	while (__tenviron[tcount_envs] != NULL)
		tcount_envs++;

	tnew_environ = taallocate_memory(sizeof(char *) * (tcount_envs + 1));
	for (tcount_envs = 0;  __tenviron[tcount_envs] != NULL; tcount_envs++)
		tnew_environ[tcount_envs] = taduplicate_string(__tenviron[tcount_envs]);

	/* Last element should will  be NULL */
	tnew_environ[tcount_envs] = NULL;
	/* Asign new for memory dynamically allocated */
	__tenviron = tnew_environ;
}

/**
 * tafree_dynamic_environ - Frees the memory to  allocated to hold "env vars"
 */
void tafree_dynamic_environ(void)
{
	tafree_dbl_ptr(__tenviron);
}
