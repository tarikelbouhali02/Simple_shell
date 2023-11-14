#include "shell.h"

/**
 * taf_strjoin - concatenates string one  + string two
 * @s1: string one
 * @s2: string two
 * Return: copy of string with null in  terminated char
 */
char *taf_strjoin(char const *s1, char const *s2)
{
	size_t	l3;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	l3 = ta_strlen(s1) + ta_strlen(s2);
	s3 = malloc(l3 + 1);
	if (s3 == NULL)
		return (NULL);
	s3[0] = '\0';
	ta_strcat(s3, s1);
	ta_strcat(s3, s2);
	s3[l3] = '\0';
	return (s3);
}

/**
 * taf_strsub - function that substract into paragraph from string
 * @s:  in string
 * @start: index ino  start
 * @len: len  in of characters to do a copy
 * Return: copy into  string with null terminated char
 */
char *taf_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	t;
	char	*us;

	us = (char *)malloc(len + 1);
	if (s == NULL || us == NULL)
		return (NULL);
	t = 0;
	while (len-- && s[start + t])
	{
		us[t] = s[start + t];
		t++;
	}
	us[t] = '\0';
	return (us);
}

/**
 * taf_memdel - function this free an array
 * @ap: array in strings
 * Return:  its void
 */
void taf_memdel(void **ap)
{
	if (ap)
	{
		free(*ap);
		*ap = NULL;
	}
}

/**
 * tf_strdel - function tths delete an array of strings
 * @as: array into its  strings
 * Return: void
 */
void tf_strdel(char **as)
{
	taf_memdel((void **)as);
}
