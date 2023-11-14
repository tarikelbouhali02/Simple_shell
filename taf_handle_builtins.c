#include "shell.h"

int taenvars_builtins(char **commands);
int taother_set_buitlins(char **commands);

/**
 * tahandle_builtins - Executes  builtin funtions in case the command is one
 * @commands: User's input parsed  an array of commads
 *
 * Return: one if the command is a builtin, zero otherwise
*/
int tahandle_builtins(char **commands)
{
	if (commands[0] == NULL)
		return (0);

	if (taenvars_builtins(commands))
		return (1);

	if (taother_set_buitlins(commands))
		return (1);

	return (0);
}

/**
 * taenvars_builtins - Verifies  a command is a builtin
 * @commands: Arrays in the commnads
 *
 * Return: one  if command is a builtin, zero otherwise
*/
int taenvars_builtins(char **commands)
{
	if (ta_strcmp(commands[0], "env") == 0)
	{
		if (commands[1] != NULL)
			return (0);

		env();
		return (1);
	}

	if (ta_strcmp(commands[0], "setenv") == 0)
	{
		if (commands[1] == NULL || commands[2] == NULL || commands[3] != NULL)
			return (1);

		ta_setenv(commands[1], commands[2]);
		return (1);
	}

	if (ta_strcmp(commands[0], "unsetenv") == 0)
	{
		if (commands[1] == NULL || commands[2] != NULL)
			return (1);

		ta_unsetenv(commands[1]);
		return (1);
	}

	return (0);
}

/**
 * taother_set_buitlins - Verifies in a command is a builtin
 * @commands: Arrays  commnads
 *
 * Return: one  if command is a builtin, zero otherwise
*/
int taother_set_buitlins(char **commands)
{
	if (ta_strcmp(commands[0], "cd") == 0)
	{
		char *path = commands[1];

		if (commands[1] == NULL)
			path = ta_getenv("HOME");

		if (path == NULL)
			path = "/";

		ta_cd(path);
		return (1);
	}

	if (ta_strcmp(commands[0], "alias") == 0)
	{
		ta_alias(commands);
		return (1);
	}

	if (ta_strcmp(commands[0], "help") == 0)
	{
		ta_help(commands);
		return (1);
	}

	if (ta_strcmp(commands[0], "history") == 0)
	{
		if (commands[1] != NULL)
		{
			taprint_builtin_error("history: No args allowed", "");
			return (1);
		}

		/* will _tahistory();*/
		/* will return (1);*/
	}

	return (0);
}
