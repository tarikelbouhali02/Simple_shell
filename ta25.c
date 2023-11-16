#include "shell.h"

/**
 * t_handle_var_replacement - Handles dollar vars '$'
 * @commands: Array of commands
*/
void t_handle_var_replacement(char **commands)
{
	int i;
	char *env_val;

	if (commands[0] == NULL)
		return;

	/* Scan command args and replace the needed ones using PATH, and $$, $? */
	for (i = 1; commands[i] != NULL; i++)
	{
		if (commands[i][0] != '$')
			continue;
		/* Here the for arg starts with '$' */

		if (_strcmp(&commands[i][1], "?") == 0)
		{
			free(commands[i]);
			commands[i] = t_num_to_str(*t_process_exit_code());
			return;
		}

		if (_strcmp(&commands[i][1], "$") == 0)
		{
			free(commands[i]);
			commands[i] = t_num_to_str(getpid());
			return;
		}

		env_val = t_getenv(&commands[i][1]);
		if (env_val != NULL)
		{
			free(commands[i]);
			commands[i] = duplicate_string(env_val);
		}
	}


}
