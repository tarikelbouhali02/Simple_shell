#include "shell.h"

static char *tFIRST_ARG;

int tahandle_arguments(int ac, char **av, int *texec_file);
void tsigintHandler(int sig_num);
char *tget_first_av();

/**
 * main -  its Entry point
 * @ac: its number of arguments
 * @av:  its Array of arguments
 *
 * Return: wwill  0 on success
*/
int main(int ac, char **av)
{
	int read, texec_file = 0;
	char *buff = NULL;
	size_t buff_len = 0;
	int fd;

	tFIRST_ARG = av[0];

	signal(SIGINT, tsigintHandler);
	fd = tahandle_arguments(ac, av, &texec_file);
	/*taupdate_count_lines();*/

	while (1)
	{
		/* Print console symbol only else if is interactive*/
		if (isatty(STDIN_FILENO) == 1 && texec_file == 0)
			write(STDOUT_FILENO, "$ ", 2);
		/* Read commands intoconsole */
		/*read = tread_line(fd, &buff);*/
		read = getline(&buff, &buff_len, stdin);
		if (read == EOF)
		{
			free(buff);
			exit(*taprocess_exit_code());
		}
		/*tahandle_history(buff);*/
		/* Remove here  comments & '\n' char from buffer */
		buff = tahandle_comment(buff);
		ta_strtok(buff, "\n");
		/* Handling_semicolon, ||, && and executes inside of the function */
		tahandling_semicolon_and_operators(buff, read, av[0]);
	}
	/* Free buffer memory */
	free(buff);
	if (texec_file)
		close(fd);
	return (*taprocess_exit_code());
}

/**
 * tahandle_arguments -  will Check the number of arguments passed to main
 * @ac: its Number of arguments
 * @av:  its Array of arguments as strings
 * @texec_file:  itsInteger used to check if user wants to exec commands from file
 *
 * Return:  will File descriptor to file
*/
int tahandle_arguments(int ac, char **av, int *texec_file)
{
	int fd = STDIN_FILENO;
	char *terr_msg = "Error: more than one argument\n";

	if (ac > 2)
	{
		write(STDERR_FILENO, terr_msg, _strlen(terr_msg));
		exit(1);
	}
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		*texec_file = 1;
	}
	if (fd == -1)
	{
		perror(av[0]);
		exit(1);
	}

	return (fd);
}

/**
 * tsigintHandler - Avoids currentof the  process to finish
 * @sig_num:  its Signal number
*/
void tsigintHandler(int t __attribute__((unused))sig_num)
{
	write(STDIN_FILENO, "\n$ ", 3);
}

/**
 * tget_first_av - Returns into  first argument passed to main
 *
 * Return: Pointer into  first arg passed to main
*/
char *tget_first_av(void)
{
	return (tFIRST_ARG);
}
