#include "shell.h"

/* GLOBAL VAR TKN_PTR */
static char *TKN_PTR = "";
static int NO_INIT_TKN_PTR = 1;

/* helper function prototype */
int _isdelimiter(char c, char *delimiter);

/**
 * t_strtok - Divides a string into tokens
 * @str: String to be divided
 * @delimiter: Delimiter by which to str will be divided
 *
 * Return: Token in string
*/
char *t_strtok(char *str, char *delimiter)
{
	char *curr_pos;
	char *tkn_start = NULL;

	if (NO_INIT_TKN_PTR == 1)
	{
		TKN_PTR = NULL;
		NO_INIT_TKN_PTR = 0;
	}

	if ((str == NULL && TKN_PTR == NULL) || (str != NULL && str[0] == '\0'))
		return (NULL);

	if (str != NULL)
		TKN_PTR = str;

	for (curr_pos = TKN_PTR; *curr_pos != '\0'; curr_pos++)
	{
		if (!_isdelimiter(*curr_pos, delimiter))
		{
			tkn_start = curr_pos;
			while (*curr_pos != '\0' && !_isdelimiter(*curr_pos, delimiter))
				curr_pos++;

			TKN_PTR = curr_pos + 1;
			if (*curr_pos == '\0')
				TKN_PTR = curr_pos;
			*curr_pos = '\0';

			return (tkn_start);
		}
	}

	return (NULL);
}

/**
 * _isdelimiter - Evaluates if a char is a delimiter or not
 * @c: Char to evaluate
 * @delimiter: Set of chars as delimiters
 *
 * Return: 1 if c it is a delimiter, 0 otherwise
*/
int _isdelimiter(char c, char *delimiter)
{
	while (*delimiter != '\0')
	{
		if (c == *delimiter)
			return (1);
		delimiter++;
	}

	return (0);
}
