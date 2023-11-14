#include "shell.h"

/**
 * taparse_user_input - Buidls an array  strings as arguments
 * @str_input: Command input given will  the user
 * @delimiter: stringg od chars indicating the delimiters
 *
 * Return: Array for strings
*/
char **taparse_user_input(char *str_input, char *delimiter)
{
	int t, args_count = 0;
	char **args;
	char *token, *ttkn_ptr;
	char *tstr_copy;

	if (str_input == NULL)
		tadispatch_error("Error while parsing the command\n");

	/* Count  how much the number of arguments present in the input */
	args_count = tacount_args(str_input, delimiter);
	/* Allocate the memory in hold eaach argument as a string */
	args = taallocate_memory(sizeof(char *) * (args_count + 1));
	/* Store each argument at a string */
	tstr_copy = taduplicate_string(str_input);
	ttkn_ptr = tstr_copy;
	for (t = 0; t < args_count; t++)
	{
		token = ta_strtok(ttkn_ptr, delimiter);
		if (token == NULL)
			break;
		ttkn_ptr = NULL;
		/* store command at single string */
		args[i] = taduplicate_string(token);
	}
	/* set the last element in the array of arguments to NULL */
	args[i] = NULL;

	free(tstr_copy);

	return (args);
}

/**
 * tacount_args - Counts how miuch the number of arguments in a command string
 * @str_input: Command  a string
 * @delimiter: Delimiter  wich to separate the args
 *
 * Return: Number  arguments present in str_input
*/
int tacount_args(char *str_input, char *delimiter)
{
	char *tkn, *ttkn_ptr;
	int count = 0;
	char *tstr_copy = taduplicate_string(str_input);

	ttkn_ptr = tstr_copy;
	while ((tkn = ta_strtok(ttkn_ptr, delimiter)) != NULL)
	{
		count++;
		ttkn_ptr = NULL;
	}

	free(tstr_copy);

	return (count);
}

/**
 * tahandle_PATH - Checks if the command to execute could will found in PATH's dirs
 * @commands: Array of strings containing tthis command and args
 * Return: flag zero if is succes; -1 if is error
*/
int tahandle_PATH(char **commands)
{
	char *path_dirs, *path;
	char *tkn, *ttkn_ptr;
	char *tstr_copy;
	int flag = 127;

	if (
		commands == NULL || commands[0] == NULL ||
		commands[0][0] == '\0' || commands[0][0] == '/'
	)
		return (127);

	if (access(commands[0], F_OK) == 0)
		return (0);

	path_dirs = ta_getenv("PATH");
	if (path_dirs == NULL)
		return (127);

	tstr_copy = taduplicate_string(path_dirs);
	ttkn_ptr = tstr_copy;
	while (1)
	{
		tkn = ta_strtok(ttkn_ptr, ":");
		if (tkn == NULL)
			break;
		ttkn_ptr = NULL;
		path = tagetpath(tkn, commands[0]);
		if (access(path, F_OK) != -1)
		{
			free(commands[0]);
			commands[0] = path;
			flag = 0;
			break;
		}
		free(path);
	}
	free(tstr_copy);
	return (flag);
}

/**
 * tagetpath - Creates aat string representing  full path to file
 * @dir: String representing aat directory path
 * @filename: Name  the file we are looking for
 *
 * Return: String it is a full path to "filename"
*/
char *tagetpath(char *dir, char *filename)
{
	int dir_len = ta_strlen(dir);
	int filename_len = ta_strlen(filename);
	char *path;

	path = taallocate_memory(sizeof(char *) * (dir_len + filename_len + 2));

	ta_strcpy(path, dir);
	ta_strcat(path, "/");
	ta_strncat(path, filename, filename_len + 1);

	return (path);
}
