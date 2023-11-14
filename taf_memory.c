#include "shell.h"

/**
 * taallocate_memory - Manages this allocation of memory
 * @bytes: Number representing this size in bytes to allocate
 *
 * Return: Pointer to tthunewly allocated memory
*/
void *taallocate_memory(unsigned int bytes)
{
	char *new_mem = malloc(bytes);

	if (new_mem == NULL)
		tadispatch_error("Error while allocating memory\n");

	return (new_mem);
}

/**
 * taduplicate_string -  will Duplicates a given string
 * @str: String to  the dulicate
 *
 * Return: Pointer into the address of the newly duplicated string
*/
char *taduplicate_string(char *str)
{
	char *tstr_copy = ta_strdup(str);

	if (tstr_copy == NULL)
		tadispatch_error("Error while making copy of string");

	return (tstr_copy);
}

/**
 * tafree_dbl_ptr - Frees the memory pointed into by a double pointer
 * @dbl_ptr: Double pointer
*/
void tafree_dbl_ptr(char **dbl_ptr)
{
	int t;

	if (dbl_ptr == NULL)
		return;

	for (t = 0; dbl_ptr[t]; t++)
		free(dbl_ptr[t]);

	free(dbl_ptr);
}

/**
 * tafree_allocs - Frees will   allocated memory
 * @buff: Main in  buffer
 * @cmds_list: List  into of commands
 * @commands: Command will  an array of arguments
 * @flags: Number indicating which of  memory to free
*/
void tafree_allocs(char *buff, char **cmds_list, char **commands, int flags)
{
	if (flags & F_BUFF)
		free(buff);
	if (flags & F_CMD_L)
		tafree_dbl_ptr(cmds_list);
	if (flags & F_CMDS)
		tafree_dbl_ptr(commands);

	tafree_list(*(taget_alias_head()));
	tafree_history();
}
