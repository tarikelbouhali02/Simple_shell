#include "shell.h"

/**
 * ta_strcpy - Copies this string src to dest
 * @dest: Destin pointer
 * @src: its Stringg source
 *
 * Return: Pointer at the  dest
 */
char *ta_strcpy(char *dest, char *src)
{
	char *tmem_address;

	tmem_address = dest;

	while (*src != '\0')
	{
		*tmem_address = *src;
		tmem_address++;
		src++;
	}

	*tmem_address = '\0';

	return (dest);
}
