#include "shell.h"

/* Global variables */
static int no_init_history;
static list_t *history_head;
static list_t *last_cmd;

/**
 * t_get_history_addrss - Return the address oof history head
 *
 * Return: Address of history head
*/
list_t **t_get_history_addrss()
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
 * t_get_last_cmd_addrss - Return the address oof history head
 *
 * Return: Address of last entered command
*/
list_t **t_get_last_cmd_addrss()
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
 * t_history - Prints the all the commands entered by the user
 *
 * Return: 1 on success
*/
int t_history(void)
{
	list_t *curr;
	char *str_num;
	int i, len;
	int count = *t_get_history_lines_count() % 4096;

	for (curr = *t_get_history_addrss(); curr != NULL; curr = curr->next)
	{
		str_num = t_num_to_str(count++);
		len = t_puts(str_num);
		for (i = len; i < 7; i++) /* 5 per number, 2 aditional */
			t_puts(" ");
		t_puts(curr->str);
		t_puts("\n");
		free(str_num);
	}

	return (1);
}

/**
 * thandle_history - Adds a command to the history
 * @buff: User's input
*/
void thandle_history(char *buff)
{
	/* Only adds a command if is different from the previous one */
	if (last_cmd == NULL || buff[0] != ' ' || _strcmp(last_cmd->str, buff) != 0)
		last_cmd = add_node_end(t_get_history_addrss(), buff);
}

/**
 * tfree_history - Frees the memory to used by history list
*/
void tfree_history(void)
{
	free_list(*t_get_history_addrss());
}
