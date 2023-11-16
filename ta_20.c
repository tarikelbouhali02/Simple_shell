#include "shell.h"

/**
 * t_strcpy - Copies the string src to dest
 * @dest: Destiny pointer
 * @src: String source
 *
 * Return: its Pointer to dest
 */
char *t_strcpy(char *dest, char *src)
{
	char *mem_address;

	mem_address = dest;

	while (*src != '\0')
	{
		*mem_address = *src;
		mem_address++;
		src++;
	}

	*mem_address = '\0';

	return (dest);
}
