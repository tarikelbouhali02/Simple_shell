#include "shell.h"

/**
 * ta_strlen - returns  length of a string
 * @s:  its array
 * Return:  will length
 */
int ta_strlen(const char *s)
{
	int t = 0;

	if (s == NULL)
		return (0);

	while (s[t])
		t++;
	return (t);
}

/**
 * ta_strdup - copy  strings with  malloc
 * @ts1: its array
 * Return: pointer into the copy
 */
char *ta_strdup(const char *ts1)
{
	char	*ts2;
	size_t	t;

	t = 0;
	ts2 = (char *)malloc(sizeof(char) * ta_strlen(ts1) + 1);
	if (!ts2)
		return (NULL);
	while (ts1[t])
	{
		ts2[t] = ts1[t];
		i++;
	}
	ts2[t] = '\0';
	return (ts2);
}

/**
 * ta_strncmp - compare else if is equal 2 strings, first n chars
 * @ts1: its string1
 * @ts2:  its string2
 * @n: n its first characters
 * Return: zero success; else pointer
 */
int	ta_strncmp(const char *ts1, const char *ts2, size_t n)
{
	size_t t;

	t = 0;
	while (t < n && ts1 && ts2 && ts1[t] && ts2[t] &&
			(unsigned char)ts1[t] == (unsigned char)ts2[t])
		t++;
	if (t == n)
		return (0);
	return ((unsigned char)ts1[t] - (unsigned char)ts2[t]);
}

/**
 * ta_strcmp - compare into is equal 2 strings
 * @ts1: its string1
 * @ts2: its  string2
 * Return: zero  success; else pointer
 */
int     ta_strcmp(const char *ts1, const char *ts2)
{
		return (ta_strncmp(ts1, ts2, (size_t)-1));
}

/**
 * tanum_to_str - Convert  number to string format
 * @num: Number into converted
 *
 * Return: Pointer into  string representation of "num"
*/
char *tanum_to_str(int num)
{
	int num_rev = 0;
	int t, digits = 0;
	char *num_str = NULL;

	if (num == 0)
		digits = 1;
	else
		while (num > 0)
		{
			digits++;
			num_rev *= 10;
			num_rev += num % 10;
			num /= 10;
		}

	num_str = malloc(sizeof(char) * (digits + 1));
	if (num_str == NULL)
		tadispatch_error("Error: Coudn't allocate memory for number conversion");

	for (t = 0; t < digits; t++)
	{
		num_str[t] = (num_rev % 10) + '0';
		num_rev /= 10;
	}
	num_str[t] = '\0';

	return (num_str);
}
