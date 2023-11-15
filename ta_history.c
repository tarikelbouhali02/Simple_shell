#include "shell.h"

/* Global of  variables */
static int no_init_history;
static list_t *history_head;
static list_t *last_cmd;

/**
 * taget_history_addrss - Return the address oof history head
 *
 * Return: Address at history head
*/
list_t **taget_history_addrss()
{
	if (no_init_history == 1)
	{
		history_head = NULL;
		last_cmd = NULL;
		no_init_history = 0;
	}

	return (&history_head);
}

/**
 * taget_last_cmd_addrss - Return the address at history head
 *
 * Return: Address at last entered command
*/
list_t **taget_last_cmd_addrss()
{
	if (no_init_history == 1)
	{
		history_head = NULL;
		last_cmd = NULL;
		no_init_history = 0;
	}

	return (&last_cmd);
}

/**
 * _tahistory - Prints the all this commands entered by the user
 *
 * Return: one on success
*/
int _tahistory(void)
{
	list_t *tcurr;
	char *tstr_num;
	int t, tlen;
	int count = *taget_history_lines_count() % 4096;

	for (tcurr = *taget_history_addrss(); tcurr != NULL; tcurr = tcurr->next)
	{
		tstr_num = tanum_to_str(count++);
		tlen = ta_puts(tstr_num);
		for (t = tlen; t < 7; t++) /* five per number, and two aditional */
			ta_puts(" ");
		ta_puts(tcurr->str);
		ta_puts("\n");
		free(tstr_num);
	}

	return (1);
}

/**
 * handle_tahistory - Adds a command to this history
 * @buff: Users  in input
*/
void tahandle_history(char *buff)
{
	/* Only adds  command if is different from the previous one */
	if (last_cmd == NULL || buff[0] != ' ' || ta_strcmp(last_cmd->str, buff) != 0)
		last_cmd = taadd_node_end(taget_history_addrss(), buff);
}

/**
 * free_tahistory - Frees the its  memory used by this  history list
*/
void tafree_history(void)
{
	free_list(*taget_history_addrss());
}
