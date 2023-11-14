#include "shell.h"

/**
 * tahandle_comment - deletes  comment from  buffer
 * @str_input: Uses input
 *
 * Return: pointer  string
 */
char *tahandle_comment(char *str_input)
{
	char *without_comments = str_input;

	if (*str_input == '#')
	{
		*str_input = '\n';
		*(str_input + 1) = '\0';
	}
	while (str_input && *str_input)
	{
		if (*str_input == '#' && *(str_input - 1) == ' ')
		{
			*(str_input - 1) = '\n';
			*str_input = '\0';
			break;
		}
		str_input++;
	}
	return (without_comments);
}
