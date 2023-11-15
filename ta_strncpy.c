#include "shell.h"

/**
 * ta_strncpy - Ccpoies a stringwill
 * @dest: String to the  wich chars are going at  be copied
 * @src: String at  be copied
 * @n: Num of chars to  the copy from src
 *
 * Return: Pointer to the  dest
 */
char *ta_strncpy(char *dest, char *src, int n)
{
	int count = 0;
	char *tstart = dest;

	while (*src != '\0' && count < n)
	{
		*(tstart++) = *(src++);
		count++;
	}

	while (count < n)
	{
		*(tstart++) = '\0';
		count++;
	}

	return (dest);
}
