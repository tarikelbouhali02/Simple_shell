#include "shell.h"

/**
 * tahandle_exit - Checks  the user entered tto exit command
 * @buff: Users input
 * @cmds_list: Array in the parsed commands
 * @commands: Users input parsed as array in the commands
 *
 * Return: zero  if the commad is NOT exit, minus one if the exit status was Illegal
*/
int tahandle_exit(char *buff, char **cmds_list, char **commands)
{
	int status;

	/* Command it NOT exit */
	if (commands[0] == NULL || ta_strcmp(commands[0], "exit") != 0)
		return (0);

	/* Command it exit */
	if (commands[1] == NULL)
	{
		tawrite_history();
		tafree_allocs(buff, cmds_list, commands, F_BUFF | F_CMDS);
		if (*taprocess_exit_code() == 127)
			exit(2);
		exit(0);
	}

	status = taget_exit_status(commands[1]);
	/* Command it exit status */
	if (status >= 0)
	{
		tawrite_history();
		tafree_allocs(buff, cmds_list, commands, F_BUFF | F_CMDS);
		exit(status);
	}

	/*  exit status passed was illegal */
	taprint_builtin_error("exit: Illegal number: ", commands[1]);
	return (-1);
}

/**
 * taget_exit_status - Calculates  exit status as a number
 * @buff: User's input
 *
 * Return: Exist status  number, -1 on error
*/
int taget_exit_status(char *buff)
{
	int t;
	int status = 0;

	for (t = 0; buff[t] != '\0'; t++)
	{
		if (buff[t] == '\n')
			return (status);

		if (buff[t] < '0' || buff[t] > '9')
			return (-1);

		status *= 10;
		status += buff[i] - '0';
	}

	return (status);
}
