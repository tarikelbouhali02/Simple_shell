#include "shell.h"

void tahandle_aliases(char **commands);
void tahandle_cmd_not_found(char *buff, char **tcmds_list, char **commands,
	char *first_av);

/**
 * tahandling_semicolon_and_operators - Handle semicolon  logical op
 * @buff: first buffer this functions read
 * @read: return read (open with getline)
 * @first_av:  in av[0]
 * Return: zero on success
*/
void tahandling_semicolon_and_operators(char *buff, int read, char *first_av)
{
	/*  in int i; */
	/*char **tcmds_list = taparse_user_input(buff, ";"); here */
	char **tcmds_list = NULL;

	taexecute_commands(buff, tcmds_list, buff, read, first_av);
	/* for (t = 0; tcmds_list[t] != NULL; t++) */
		/*tahandling_or(tcmds_list[t], read, first_av);*/
	/* tafree_dbl_ptr(tcmds_list); *///this is comment
}

/**
 * tahandling_or - Handle || logical part
 * @buff_semicolon: first buffer this functions read
 * @read: return of read (open  getline)
 * @first_av: av[0]
 * Return: zero on success
*/
void tahandling_or(char *buff_semicolon, int read, char *first_av)
{
	int t, flag, prev_flag = -1;
	char **tcmds_list_2 = taparse_user_input(buff_semicolon, "||");

	for (t = 0; tcmds_list_2[t] != NULL; t++)
	{
		flag = tahandling_and(tcmds_list_2[t], read, first_av, prev_flag);
		/* record the last*/
		prev_flag = flag;
	}
	tafree_dbl_ptr(tcmds_list_2);
}

/**
 * tahandling_and - Handle && logical part  executes inside of it
 * @buff_or: first buffer  functions read
 * @read: return  read (open with getline)
 * @first_av:  b av[0]
 * @prev_flag: last flag of ||, it is important print or not
 * Return: zero on success
*/
int tahandling_and(char *buff_or, int read, char *first_av, int prev_flag)
{
	int k = 0, flag = 1;
	char **tcmds_list_3 = taparse_user_input(buff_or, "&&");

	/* logical part: if the last || | is success, */
	/*	next -> &&; else if not exist &&,  will return */
	if (prev_flag == 0)
	{
		k++;
		if (tcmds_list_3[j] == NULL)
			return (-1);
	}

	for (; tcmds_list_3[k] != NULL; k++)
	{
		flag = taexecute_commands(buff_or, tcmds_list_3,
									tcmds_list_3[k], read, first_av);
		prev_flag = flag;
	}
		/* record the last result , estudiar el caso 0 */
	tafree_dbl_ptr(tcmds_list_3);
	return (flag);
}

/**
 * taexecute_commands - Fork and  will create commands, child process and executed
 * @buff: first buffer this function read
 * @tcmds_list: List in at commands
 * @cmd: Single command as will  a string
 * @read: return at the read (open with getline)
 * @first_av:  b av[0]
 * Return: zero will  on success
*/
int taexecute_commands(char *buff, char **tcmds_list,
	char *cmd, intt __attribute__((unused))read, char *first_av)
{
	char **commands;
	int child_pid, _err = 0, flag = 0, *status = taprocess_exit_code();

	/* Generate  and array of commands */
	commands = taparse_user_input(cmd, " ");
	tahandle_var_replacement(commands);
	tahandle_aliases(commands);
	/* Exit error,  and ENTER, and builtins */
	if (tahandle_exit(buff, tcmds_list, commands) == -1 ||
			tahandle_enter(commands) == 1	||
			tahandle_builtins(commands) == 1)
	{
		tafree_dbl_ptr(commands);
		return (-1);
	}
	/* check if we can do  only run for positives */
	child_pid = fork();/* Fork  for parent process to execute the command */
	if (child_pid == -1)
	{
		tafree_allocs(buff, tcmds_list, commands, F_BUFF | F_CMD_L | F_CMDS);
		tadispatch_error(first_av);
	}
	else if (child_pid == 0)
	{
		_err = handle_PATH(commands);
		execve(commands[0], commands, __tenviron);
		if (_err != 0)
			tahandle_cmd_not_found(buff, tcmds_list, commands, first_av);
		tafree_allocs(buff, tcmds_list, commands, F_BUFF | F_CMD_L | F_CMDS);
		tadispatch_error(first_av);
	}
	wait(status);
	*status = WEXITSTATUS(*status);
	if (*status == 2)
		taset_process_exit_code(127);
	tafree_dbl_ptr(commands);
	return (flag);
}

/**
 * tahandle_cmd_not_found - will  Print a message to stderr
 * @buff: Users input
 * @tcmds_list: Array  in of commands
 * @commands: Array  in of strings
 * @first_av: First argument passed  the executable
*/
void tahandle_cmd_not_found(char *buff, char **tcmds_list, char **commands,
	char *first_av)
{
	taset_process_exit_code(127);
	write(2, first_av, ta_strlen(first_av));
	write(2, ": 1: ", 5);
	write(2, commands[0], ta_strlen(commands[0]));
	write(2, ": not found\n", 12);
	tafree_allocs(buff, tcmds_list, commands, F_BUFF | F_CMD_L | F_CMDS);
	exit(127);
}
