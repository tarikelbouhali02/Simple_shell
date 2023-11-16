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
/* open */
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

/* FLAGS */
#define F_BUFF 1
#define F_CMD_L 2
#define F_CMDS 4

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton project
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

/*linked lists*/
size_t t_print_list(const list_t *h);
list_t *add_node_end(list_t **head, const char *str);
void free_list(list_t *head);

char *t_get_first_av(void);

/*function with all the logical part that will work with the main */
int t_execute_commands(char *buff, char **cmds_list, char *cmd,int read, char *first_av);
void _handling_semicolon_and_operators(char *buff, int read, char *first_av);
void t_handling_or(char *buff_semicolon, int read, char *first_av);
int t_handling_and(char *buff_semicolon, int read,char *first_av, int prev_flag);

/* Special functions */
void __attribute__((constructor)) t_build_dynamic_environ(void);
void __attribute__((destructor)) t_free_dynamic_environ(void);

char *_getenv(char *name);

/* replacement variables */
void t_handle_var_replacement(char **commands);
int *t_process_exit_code();
void _tset_process_exit_code(int code);

/* builtins */
void _env(void);
int t_setenv(char *name, char *value);
int _unsetenv(char *name);
int t_cd(char *path);
int t_alias(char **commands);
int t_help(char **commands);
int t_history(void);
/* helper global vars builtin functions */
list_t **get_alias_head();
list_t **t_get_history_addrss();
list_t **t_get_last_cmd_addrss();
void thandle_history(char *buff);
void tfree_history(void);
void _write_history(void);
void t_update_count_lines(void);
int *get_history_lines_count();

/* builtins utils */
int t_validate_env_name(char *name);
int t_t_is_valid_env_var_name(char *name);
int t_get_env_index(char *name);
void t_set_alias(char *alias_pair);
int t_is_set_alias(char *alias_pair);
int handl_e_alias_args(char **commands, list_t **out_addrs);
/* functions that is part of help */
int tread_line(const int fd, char **line);
int f_read_line(char **str, char **line, int fd);

/* own implementations */
char *t_strtok(char *str, char *delimiter);
int _getline(char **buffer, size_t *buf_size, FILE *stream);
char *t_strcpy(char *dest, char *src);
char *t_strncpy(char *dest, char *src, int n);

/* Command handlers */
int t_handle_PATH(char **commands);
char *t_getpath(char *dir, char *filename);
char **t_parse_user_input(char *str_input, char *delimiter);
int t_count_args(char *str_input, char *delimiter);

/* Memory management */
void *allocate_memory(unsigned int bytes);
char *duplicate_string(char *str);
void t_free_dbl_ptr(char **dbl_ptr);
void _free_allocs(char *buff, char **cmds_list, char **commands, int flags);

void *t_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* _handle_builtins */
int _handle_builtins(char **commands);

/* _handle_enter */
int _handle_enter(char **commands);
/* handle comments in input */
char *_handle_comment(char *str_input);

/* Exit handlers */
int thandle_exit(char *buff, char **cmds_list, char **commands);
int tget_exit_status(char *buff);

/* Error handlers */
void tdispatch_error(char *msg);
void print_tbuiltin_error(char *msg, char *arg);

/* strings functions */
int _tstrlen(const char *s);
char *t_strdup(const char *s1);
char *t_strchr(const char *s, int c);
char *t_strcat(char *s1, const char *s2);
char *t_strncat(char *s1, const char *s2, size_t n);
char *t_num_to_str(int num);
int	t_strncmp(const char *s1, const char *s2, size_t n);
int t_puts(char *str);

/* f_strings_creations */
char *t_strjoin(char const *s1, char const *s2);
char *t_strsub(char const *s, unsigned int start, size_t len);
void t_strdel(char **as);
int _strcmp(const char *s1, const char *s2);

#endif /* __SHELL_H */
