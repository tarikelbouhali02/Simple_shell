#ifndef __SHELL_H
#define __SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
/*  its open */
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

/*  its FLAGS */
#define F_BUFF 1
#define F_CMD_L 2
#define F_CMDS 4

/**
 * struct list_s -  will singly linked list
 * @str: string - will  (malloc'ed string)
 * @len: length into string
 * @next: points into next node
 *
 * Description:  itssingly linked list node structure
 * for Holberton project
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

/* its linked lists*/
size_t taprint_list(const list_t *h);
list_t *taadd_node_end(list_t **head, const char *str);
void tafree_list(list_t *head);

char *tget_first_av(void);

/* its function with all the logical part that will work with the main */
int taexecute_commands(char *buff, char **cmds_list, char *cmd,
											int read, char *first_av);
void tahandling_semicolon_and_operators(char *buff, int read, char *first_av);
void tahandling_or(char *buff_semicolon, int read, char *first_av);
int tahandling_and(char *buff_semicolon, int read,
											char *first_av, int prev_flag);

/* its  Special functions */
void t__attribute__((constructor)) tabuild_dynamic_environ(void);
void t__attribute__((destructor)) tafree_dynamic_environ(void);

char *ta_getenv(char *name);

/* its replacement variables */
void tahandle_var_replacement(char **commands);
int *taprocess_exit_code();
void taset_process_exit_code(int code);

/*  its builtins */
void taenv(void);
int ta_setenv(char *name, char *value);
intta ta_unsetenv(char *name);
int ta_cd(char *path);
int ta_alias(char **commands);
int ta_help(char **commands);
int _tahistory(void);
/* its helper global vars builtin functions */
list_t **taget_alias_head();
list_t **taget_history_addrss();
list_t **taget_last_cmd_addrss();
void tahandle_history(char *buff);
void tafree_history(void);
void tawrite_history(void);
void taupdate_count_lines(void);
int *taget_history_lines_count();

/*its  builtins utils */
int tavalidate_env_name(char *name);
int tais_valid_env_var_name(char *name);
int taget_env_index(char *name);
void set_alias(char *alias_pair);
int tais_set_alias(char *alias_pair);
int tahandle_alias_args(char **commands, list_t **out_addrs);
/*its  functions that is part of help */
int tread_line(const int fd, char **line);
int taf_read_line(char **str, char **line, int fd);

/*its  own implementations */
char *ta_strtok(char *str, char *delimiter);
int _getline(char **buffer, size_t *buf_size, FILE *stream);
char *ta_strcpy(char *dest, char *src);
char *ta_strncpy(char *dest, char *src, int n);

/*its  Command handlers */
int tahandle_PATH(char **commands);
char *tagetpath(char *dir, char *filename);
char **taparse_user_input(char *str_input, char *delimiter);
int tacount_args(char *str_input, char *delimiter);

/*its  Memory management */
void *taallocate_memory(unsigned int bytes);
char *taduplicate_string(char *str);
void tafree_dbl_ptr(char **dbl_ptr);
void tafree_allocs(char *buff, char **cmds_list, char **commands, int flags);

void *ta_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* its its tahandle_builtins */
int tahandle_builtins(char **commands);

/*its  tahandle_enter */
int tahandle_enter(char **commands);
/*its  handle comments in input */
char *tahandle_comment(char *str_input);

/*its  Exit handlers */
int tahandle_exit(char *buff, char **cmds_list, char **commands);
int taget_exit_status(char *buff);

/*its  Error handlers */
void tadispatch_error(char *msg);
void taprint_builtin_error(char *msg, char *arg);

/* strings functions */
/*uts strings functions */
int ta_strlen(const char *s);
char *ta_strdup(const char *s1);
char *_strchr(const char *s, int c);
char *ta_strcat(char *s1, const char *s2);
char *ta_strncat(char *s1, const char *s2, size_t n);
char *tanum_to_str(int num);
int	ta_strncmp(const char *s1, const char *s2, size_t n);
int ta_puts(char *str);

/*its  f_strings_creations */
char *taf_strjoin(char const *s1, char const *s2);
char *taf_strsub(char const *s, unsigned int start, size_t len);
void tf_strdel(char **as);
int ta_strcmp(const char *s1, const char *s2);

#endif /*i __SHELL_H */
