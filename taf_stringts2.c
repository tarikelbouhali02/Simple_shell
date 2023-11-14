#include "shell.h"

/**
 * ta_strchr - string in scanning operation
 * @s: string one 
 * @c: character into  search
 * Return: return  pointer into byte, or
 * a null pointer else if the byte was not found.
 */
char *ta_strchr(const char *s, int c)
{
	size_t t;

	t = 0;
	while (s[t])
	{
		if (s[t] == c)
			return ((char *)&s[t]);
		t++;
	}
	if (c == '\0')
		return ((char *)(&s[t]));
	return (NULL);
}

/**
 * ta_strcat - its concatenate two strings
 * @ts1: string one 
 * @ts2: string two 
 * Return:  will return a pointer to the resulting string dest.
 */
char *ta_strcat(char *ts1, const char *ts2)
{
	return (ta_strncat(ts1, ts2, -1));
}

/**
 * ta_strncat - concatenate first n chars of stwo to sone string
 * @ts1: its string one
 * @ts2: string two
 * @n: numbers of characters of stwo to concatenate to the ts1
 * Return:  will return a pointer to the resulting string dest.
 */
char *ta_strncat(char *ts1, const char *ts2, size_t n)
{
	size_t t;
	size_t j;

	t = ta_strlen(ts1);
	k = 0;
	while (ts2[j] && k < n)
		ts1[t++] = ts2[k++];
	ts1[t] = '\0';
	return (ts1);
}
