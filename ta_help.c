#include "shell.h"
#define BUFF_SIZE 32

/**
 * tread_line - print a line at fd
 * @fd: file decriptor
 * @line: line at text
 * Return: execution of tread_line: one if success
 */
int tread_line(const int fd, char **line)
{
	int			reader;
	char		*tmp;
	char		buffer[BUFF_SIZE + 1];
	static char	*str[4864];

	if (fd < 0 || BUFF_SIZE <= 0 || line == NULL || read(fd, buffer, 0) < 0)
		return (-1);
	while ((reader = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[reader] = '\0';
		if (!str[fd])
			str[fd] = ta_strdup(buffer);
		else
		{
			tmp = f_strjoin(str[fd], buffer);
			free(str[fd]);
			str[fd] = tmp;
		}
		if (ta_strchr(str[fd], '\n'))
			break;
	}
	if (str[fd] == NULL && reader == 0)
		return (-1);
	return (taf_read_line(str, line, fd));
}

/**
 * taf_read_line - read in line from fd
 * @str: grip at documment
 * @fd: file decriptor
 * @line: line  text
 * Return: one if success
 */
int	taf_read_line(char **str, char **line, int fd)
{
	char	*tmp;
	int		count;

	count = 0;
	while (str[fd][count] != '\0' && str[fd][count] != '\n')
		count++;
	*line = taf_strsub(str[fd], 0, count);
	if (str[fd][count] == '\n')
	{
		tmp = ta_strdup(&str[fd][count + 1]);
		free(str[fd]);
		str[fd] = tmp;
		if (str[fd][0] == '\0')
			tf_strdel(&str[fd]);
	}
	else
		tf_strdel(&str[fd]);
	return (1);
}

/**
 * ta_help - functionsits  this simulate help command
 * @commands: array of strings too execute
 * Return: zero if is positive (one is true min.); minus one if is error
 */
int ta_help(char **commands)
{

	int fd, t = 1, tresult = -1;
	char *line = NULL;

	while (commands[t])
	{
		fd = open(commands[t], O_RDONLY);
		if (fd != -1)
		{
			tresult = 0;
			while (tread_line(fd, &line) == 1)
			{
				puts(line);
				free(line);
			}
			close(fd);
		}
		t++;
	}

	return (tresult);
}
