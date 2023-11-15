#include "shell.h"

/**
 * tahandle_var_replacement - Handles dollar vars will show this  '$'
 * @commands: Array at commands
*/
void tahandle_var_replacement(char **commands)
{
	int t;
	char *tenv_val;

	if (commands[0] == NULL)
		return;

	/* Scan command args and replace the needed ones using PATH, and two  $$, $? */
	for (t = 1; commands[t] != NULL; t++)
	{
		if (commands[t][0] != '$')
			continue;
		/* Here the arg starts wth '$' */

		if (ta_strcmp(&commands[t][1], "?") == 0)
		{
			free(commands[t]);
			commands[t] = tanum_to_str(*taprocess_exit_code());
			return;
		}

		if (ta_strcmp(&commands[t][1], "$") == 0)
		{
			free(commands[t]);
			commands[t] = tanum_to_str(getpid());
			return;
		}

		tenv_val = ta_getenv(&commands[t][1]);
		if (tenv_val != NULL)
		{
			free(commands[t]);
			commands[t] = taduplicate_string(tenv_val);
		}
	}

}
