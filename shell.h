#ifndef SHELL_H
#define SHELL_H

/*---LIBRARIES---*/
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
/*---PROTOTYPES---*/
/* main.c */
/*---LIBRARIES---*/
/*---Macros---*/
#define TOK_DELIM " \t\r\n\a\""
extern char **environ;
/*---PROTOTYPES---*/
/* main.c */
void tshell_interactive(void);
void tshell_no_interactive(void);
/* tshell_interactive.c */
char *rread_line(void);
char **ssplit_line(char *line);
int texecute_args(char **args);
/* texecute_args */
int tnew_process(char **args);
/* tshell_no_interactive */
char *rread_stream(void);
/*---Builtin func---*/
int own_cd(char **args);
int own_exit(char **args);
int own_env(char **args);
int own_help(char **args);
#endif
