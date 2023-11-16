#include "shell.h"

void t_handle_aliases(char **commands);
void handle_cmd_not_found(char *buff, char **cmds_list, char **commands,
	char *first_av);

/**
 * _handling_semicolon_and_operators - Handle semicolon and logical op
 * @buff: first buffer that functions read
 * @read: return of read (open with getline)
 * @first_av: av[0]
 * Return: 0 on success
*/
void _handling_semicolon_and_operators(char *buff, int read, char *first_av)
{
	/* int i; */
	/*char **cmds_list = t_parse_user_input(buff, ";");*/
	char **cmds_list = NULL;

	t_execute_commands(buff, cmds_list, buff, read, first_av);
	/* for (i = 0; cmds_list[i] != NULL; i++) */
		/*t_handling_or(cmds_list[i], read, first_av);*/
	/* t_free_dbl_ptr(cmds_list); */
}

/**
 * t_handling_or - Handle || logical part
 * @buff_semicolon: first buffer that functions read
 * @read: return of read (open with getline)
 * @first_av: av[0]
 * Return: 0 on success
*/
void t_handling_or(char *buff_semicolon, int read, char *first_av)
{
	int i, flag, prev_flag = -1;
	char **cmds_list_2 = t_parse_user_input(buff_semicolon, "||");

	for (i = 0; cmds_list_2[i] != NULL; i++)
	{
		flag = t_handling_and(cmds_list_2[i], read, first_av, prev_flag);
		/* record de last*/
		prev_flag = flag;
	}
	t_free_dbl_ptr(cmds_list_2);
}

/**
 * t_handling_and - Handle && logical part and executes inside of it
 * @buff_or: first buffer that functions read
 * @read: return of read (open with getline)
 * @first_av: av[0]
 * @prev_flag: last flag of ||, it is important to print or not
 * Return: 0 on success
*/
int t_handling_and(char *buff_or, int read, char *first_av, int prev_flag)
{
	int j = 0, flag = 1;
	char **cmds_list_3 = t_parse_user_input(buff_or, "&&");

	/* logical part: if the last || is success, */
	/*	next -> &&; if not exist &&, return */
	if (prev_flag == 0)
	{
		j++;
		if (cmds_list_3[j] == NULL)
			return (-1);
	}

	for (; cmds_list_3[j] != NULL; j++)
	{
		flag = t_execute_commands(buff_or, cmds_list_3,
									cmds_list_3[j], read, first_av);
		prev_flag = flag;
	}
		/* record de last result , estudiar el caso 0 */
	t_free_dbl_ptr(cmds_list_3);
	return (flag);
}

/**
 * t_execute_commands - Fork and create commands, child process and executed
 * @buff: first buffer that function read
 * @cmds_list: List of commands
 * @cmd: Single command as a string
 * @read: return of read (open with getline)
 * @first_av: av[0]
 * Return: 0 on success
*/
int t_execute_commands(char *buff, char **cmds_list,
	char *cmd, int __attribute__((unused))read, char *first_av)
{
	char **commands;
	int child_pid, _err = 0, flag = 0, *status = t_process_exit_code();

	/* Generate array of commands */
	commands = t_parse_user_input(cmd, " ");
	t_handle_var_replacement(commands);
	t_handle_aliases(commands);
	/* Exit error, ENTER, and builtins */
	if (thandle_exit(buff, cmds_list, commands) == -1 ||
			_handle_enter(commands) == 1	||
			_handle_builtins(commands) == 1)
	{
		t_free_dbl_ptr(commands);
		return (-1);
	}
	/* check if we can only run for positives */
	child_pid = fork();/* Fork parent process to execute the command */
	if (child_pid == -1)
	{
		_free_allocs(buff, cmds_list, commands, F_BUFF | F_CMD_L | F_CMDS);
		tdispatch_error(first_av);
	}
	else if (child_pid == 0)
	{
		_err = t_handle_PATH(commands);
		execve(commands[0], commands, __environ);
		if (_err != 0)
			handle_cmd_not_found(buff, cmds_list, commands, first_av);
		_free_allocs(buff, cmds_list, commands, F_BUFF | F_CMD_L | F_CMDS);
		tdispatch_error(first_av);
	}
	wait(status);
	*status = WEXITSTATUS(*status);
	if (*status == 2)
		set_process_exit_code(127);
	t_free_dbl_ptr(commands);
	return (flag);
}

/**
 * handle_cmd_not_found - Print a message to stderr
 * @buff: User's input
 * @cmds_list: Array of commands
 * @commands: Array of strings
 * @first_av: First argument passed to the executable
*/
void handle_cmd_not_found(char *buff, char **cmds_list, char **commands,
	char *first_av)
{
	set_process_exit_code(127);
	write(2, first_av,_tstrlen(first_av));
	write(2, ": 1: ", 5);
	write(2, commands[0],_tstrlen(commands[0]));
	write(2, ": not found\n", 12);
	_free_allocs(buff, cmds_list, commands, F_BUFF | F_CMD_L | F_CMDS);
	exit(127);
}
