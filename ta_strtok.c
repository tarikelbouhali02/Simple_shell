#include "shell.h"

/* GLOBAL VAR TKN_PTR */
static char *TKN_PTR = "";
static int NO_INIT_TKN_PTR = 1;

/* helper function prototype */
int taisdelimiter(char c, char *delimiter);

/**
 * ta_strtok - Divides a string into tokens
 * @str: String to be divided
 * @delimiter: Delimiter by which to str will be divided
 *
 * Return: Token in string
*/
char *ta_strtok(char *str, char *delimiter)
{
	char *tcurr_pos;
	char *ttkn_start = NULL;

	if (NO_INIT_TKN_PTR == 1)
	{
		TKN_PTR = NULL;
		NO_INIT_TKN_PTR = 0;
	}

	if ((str == NULL && TKN_PTR == NULL) || (str != NULL && str[0] == '\0'))
		return (NULL);

	if (str != NULL)
		TKN_PTR = str;

	for (tcurr_pos = TKN_PTR; *tcurr_pos != '\0'; tcurr_pos++)
	{
		if (!taisdelimiter(*tcurr_pos, delimiter))
		{
			ttkn_start = tcurr_pos;
			while (*tcurr_pos != '\0' && !taisdelimiter(*tcurr_pos, delimiter))
				tcurr_pos++;

			TKN_PTR = tcurr_pos + 1;
			if (*tcurr_pos == '\0')
				TKN_PTR = tcurr_pos;
			*tcurr_pos = '\0';

			return (ttkn_start);
		}
	}

	return (NULL);
}

/**
 * taisdelimiter - Evaluates if a  char it is  a delimiter or not
 * @c: Char to the  evaluate
 * @delimiter: Set of will  a chars as delimiters
 *
 * Return: one  if c is a delimiter, zero otherwise
*/
int taisdelimiter(char c, char *delimiter)
{
	while (*delimiter != '\0')
	{
		if (c == *delimiter)
			return (1);
		delimiter++;
	}

	return (0);
}
