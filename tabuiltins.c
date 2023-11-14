#include "shell.h"

/**
 * taenv - Prints to the environment variables to the  stdout
*/
void taenv(void)
{
	int i;
	char **env = __tenviron;

	for (i = 0; env[i]; i++)
	{
		write(STDOUT_FILENO, env[i], ta_strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	taset_process_exit_code(0);
}

/**
 * ta_setenv - Sets ||  adds at environment variable
 * @name: Name for  to  new env variable
 * @value: Value for  new env variable
 *
 * Return: one on success, minus one on error
 */
int ta_setenv(char *name, char *value)
{
	int env_index, new_var_len;

	if (tavalidate_env_name(name) == -1)
		return (-1);

	env_index = taget_env_index(name);
	if (env_index == -1)
	{/* var doesn't exist, SO CREATE IT */
		int env_count = 0;
		int old_size, new_size;

		while (__tenviron[env_count] != NULL)
			env_count++;

		old_size = sizeof(char *) * (env_count);
		new_size = sizeof(char *) * (env_count + 2);
		__tenviron = ta_realloc(__tenviron, old_size, new_size);
		if (__tenviron == NULL)
			tadispatch_error("Error while ta_reallocating memory for new env var");

		/* The new value will be stored at  the index env_count */
		env_index = env_count;
		/* last value For the for  new taenv var needs to be NULL */
		__tenviron[env_count + 1] = NULL;
	}
	else
	{
		/* var exists, so boverwrite it's value */
		free(__tenviron[env_index]);
	}

	new_var_len = ta_strlen(name) + ta_strlen(value) + 2;
	/* store at env var either  it  is exists or it needs to be overwritten */
	__tenviron[env_index] = taallocate_memory(sizeof(char) * new_var_len);
	ta_strcpy(__tenviron[env_index], name);
	ta_strcat(__tenviron[env_index], "=");
	ta_strcat(__tenviron[env_index], value);

	taset_process_exit_code(0);
	return (1);
}

/**
 *ta ta_unsetenv - Removes at evironment variable
 * @name: Name to the for new taenv variable
 *
 * Return: one on success, minus one on error
 */
int ta_unsetenv(char *name)
{
	int env_index, i;

	env_index = taget_env_index(name);
	if (env_index >= 0)
	{/* var exists, We  unset it */
		free(__tenviron[env_index]);

		for (i = env_index; __tenviron[i] != NULL; i++)
			__tenviron[i] = __tenviron[i + 1];

		taset_process_exit_code(0);
		return (1);
	}

	/* Var doesn't exist, we  print error or do nothing */
	taset_process_exit_code(0); /* Indicates that no error ocurred */

	return (1);
}

/**
 * ta_cd - Changes tat current directory at the process
 * @path: Path too wich change at the working directory
 *
 * Return: one on success, minus one on error
*/
int ta_cd(char *path)
{
	char buff[1024];
	char *oldpwd;
	char *_path = path;

	if (ta_strcmp(path, "-") == 0)
		path = ta_getenv("OLDPWD");

	if (path == NULL)
	{
		print_builtin_error("cd: OLDPWD not set", "");
		return (-1);
	}
	/* Needed the avoid reading onn freed memory */
	path = taduplicate_string(path);
	/* store this dir it is case for update */
	oldpwd = getcwd(buff, 1024);
	if (oldpwd == NULL)
	{
		free(path);
		print_builtin_error("cd: couldn't get current dir", "");
		return (-1);
	}
	/* Try to the  change the current dir */
	if (chdir(path) == -1)
	{
		free(path);
		print_builtin_error("cd: can't change cd to ", _path);
		taset_process_exit_code(1);
		return (-1);
	}
	/* Update taenv variables */
	ta_setenv("OLDPWD", oldpwd);
	ta_setenv("PWD", path);
	free(path);
	taset_process_exit_code(0);
	return (1);
}

/**
 * ta_alias - Sets an alias command
 * @commands: List of commands
 *
 * Return:minus one on error, 0 otherwise
*/
int ta_alias(char **commands)
{
	int status = 0;
	list_t *curr;
	list_t *out_head = NULL;
	list_t **alias_addrs = get_alias_head();

	/* the alias args starts from the  position 1 */
	if (commands[1] == NULL)
	{ /* This means to list all at  the aliases */
		for (curr = *alias_addrs; curr != NULL; curr = curr->next)
		{
			ta_puts(curr->str);
			ta_puts("\n");
		}
		taset_process_exit_code(0);
		return (1);
	}
	/* List aliases  sets the aliases that have form name=value */
	status = handle_alias_args(commands, &out_head);
	/* print listed  at thealias */
	for (curr = out_head; curr != NULL; curr = curr->next)
	{
		ta_puts(curr->str);
		ta_puts("\n");
	}
	/* free here  list */
	tafree_list(out_head);
	return (status);
}
