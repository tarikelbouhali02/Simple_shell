#include "shell.h"

/**
 * t_strncpy - Ccpoies a string
 * @dest: String to wich chars are going to be copied
 * @src: String to be copied
 * @n: Num of the chars to copy from src
 *
 * Return: Pointer to dest
 */
char *t_strncpy(char *dest, char *src, int n)
{
	int count = 0;
	char *start = dest;

	while (*src != '\0' && count < n)
	{
		*(start++) = *(src++);
		count++;
	}

	while (count < n)
	{
		*(start++) = '\0';
		count++;
	}

	return (dest);
}
