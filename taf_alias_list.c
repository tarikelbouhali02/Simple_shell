#include "shell.h"

static int not_init_alias_head = 1;
static list_t *alias_head;

/**
 * taget_alias_head - Returns alias_head *pointer
 *
 * Return: Pointer to alias show var
*/
list_t **taget_alias_head()
{
	if (not_init_alias_head == 1)
	{
		alias_head = NULL;
		not_init_alias_head = 0;
	}
	return (&alias_head);
}

/**
 * tais_set_alias - Checks at  alias input it meant to the  set an alias
 * @alias_pair: String alias arg input
 *
 * Return: one for true, zero otherwise
*/
int tais_set_alias(char *alias_pair)
{
	int i;

	/* Check at this '=' sign */
	/* the '=' sign shouldn't in this indx 0 */
	for (i = 1; alias_pair[i] != '\0'; i++)
		if (alias_pair[i] == '=')
			return (1);

	return (0);
}

/**
 * taset_alias - adds | |  updates aliases
 * @alias_pair: String at this form name=value
*/
void taset_alias(char *alias_pair)
{
	char tmp_buff[250];
	int first_eq, last_eq;
	list_t *curr;
	list_t **alias_addrs = taget_alias_head();

	/* Find first this  '=' sign */
	for (first_eq = 1; alias_pair[first_eq] != '\0'; first_eq++)
		if (alias_pair[first_eq] == '=')
			break;

	/* Copy at this text before '=' */
	strncpy(tmp_buff, alias_pair, first_eq);
	tmp_buff[first_eq] = '\0';
	/* Append = and will  ' symbols */
	ta_strcat(tmp_buff, "='");

	/* Find last eq in case at the  putting '=' secuentially */
	for (last_eq = first_eq; alias_pair[last_eq] != '\0'; last_eq++)
		if (alias_pair[last_eq] != '=')
			break;

	/* Copy the second part at  this alias */
	ta_strcat(tmp_buff, &alias_pair[last_eq]);
	ta_strcat(tmp_buff, "'");

	/* Add alias at this global list */
	for (curr = *alias_addrs; curr != NULL; curr = curr->next)
		if (ta_strncmp(curr->str, alias_pair, first_eq) == 0 &&
				(curr->str)[first_eq] == '=')
		{ /* Update already in  existing alias */
			free(curr->str);
			curr->str = ta_strdup(tmp_buff);
			return;
		}

	/* Add new alias at this list */
	taadd_node_end(alias_addrs, tmp_buff);
}

/**
 * tahandle_alias_args - Evaluates alias input command will decides what to do
 * @commands: Arrays in commands
 * @out_addrs: Pointer at the out's head node
 *
 * Return: minus one if error happens, zero otherwise
*/
int tahandle_alias_args(char **commands, list_t **out_addrs)
{
	int i, len, was_alias;
	int status = 0;
	list_t *curr;
	list_t **alias_addrs = taget_alias_head();

	taset_process_exit_code(0);
	for (i = 1; commands[i] != NULL; i++)
	{
		was_alias = 0;
		len = ta_strlen(commands[i]);
		/* Check that if user it is trying to print an alias */
		for (curr = *alias_addrs; curr != NULL; curr = curr->next)
		{
			if (ta_strncmp(curr->str, commands[i], len) == 0 && (curr->str)[len] == '=')
			{ /* Means at the list an alias */
				was_alias = 1;
				taadd_node_end(out_addrs, curr->str);
				break;
			}
		}
		if (was_alias)
			continue;
		/* Here, user is trying at the set an alias or print an unexistent one */
		if (tais_set_alias(commands[i]))
			taset_alias(commands[i]); /* Validate that it is set format is fine */
		else /* Print errors */
		{
			status = -1;
			taset_process_exit_code(1);
			ta_puts("alias: ");
			ta_puts(commands[i]);
			ta_puts(" not found\n");
		}
	}

	return (status);
}

/**
 * tahandle_aliases - Handle alias replacement
 * @commands: Arrays in the commands
*/
void tahandle_aliases(char **commands)
{
	list_t *curr;
	list_t **alias_addrs = taget_alias_head();
	int cmd_len = ta_strlen(commands[0]);
	char *str;
	char tmp_buff[250];
	int i, alias_len = 0;

	if (commands[0] == NULL)
		return;

	/* Initialize buffer */
	for (i = 0; i < 250; i++)
		tmp_buff[i] = '\0';

	/* Search in  a command is an alias */
	for (curr = *alias_addrs; curr != NULL; curr = curr->next)
	{
		str = curr->str;
		if (ta_strncmp(commands[0], str, cmd_len) == 0 && str[cmd_len] == '=')
		{ /* the command it is  an alias */
			alias_len = ta_strlen(&str[cmd_len + 2]); /* +2 b "='" chars */
			strncpy(tmp_buff, &str[cmd_len + 2], alias_len - 1);
			tmp_buff[alias_len] = '\0';
			/* Free and then update at this command */
			free(commands[0]);
			commands[0] = taduplicate_string(tmp_buff);
			break;
		}
	}
}
