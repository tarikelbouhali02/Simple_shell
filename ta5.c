#include "shell.h"

/**
 * allocate_memory - Manages the allocation of memory
 * @bytes: Number representing the size in bytes to allocate
 *
 * Return: Pointer to the newly allocated memory
*/
void *allocate_memory(unsigned int bytes)
{
	char *new_mem = malloc(bytes);

	if (new_mem == NULL)
		tdispatch_error("Error while allocating memory\n");

	return (new_mem);
}

/**
 * duplicate_string - Duplicates a given string
 * @str: String to dulicate
 *
 * Return: Pointer to the address of the newly duplicated string
*/
char *duplicate_string(char *str)
{
	char *str_copy = t_strdup(str);

	if (str_copy == NULL)
		tdispatch_error("Error while making copy of string");

	return (str_copy);
}

/**
 * t_free_dbl_ptr - Frees the memory pointed to by a double pointer
 * @dbl_ptr: Double pointer
*/
void t_free_dbl_ptr(char **dbl_ptr)
{
	int i;

	if (dbl_ptr == NULL)
		return;

	for (i = 0; dbl_ptr[i]; i++)
		free(dbl_ptr[i]);

	free(dbl_ptr);
}

/**
 * _free_allocs - Frees allocated memory
 * @buff: Main buffer
 * @cmds_list: List of commands
 * @commands: Command as an array of arguments
 * @flags: Number indicating which memory to free
*/
void _free_allocs(char *buff, char **cmds_list, char **commands, int flags)
{
	if (flags & F_BUFF)
		free(buff);
	if (flags & F_CMD_L)
		t_free_dbl_ptr(cmds_list);
	if (flags & F_CMDS)
		t_free_dbl_ptr(commands);

	free_list(*(get_alias_head()));
	tfree_history();
}
