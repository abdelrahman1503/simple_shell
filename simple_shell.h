#ifndef _SIMPLE_SHELL_H_
#define _SIMPLE_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} st_list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} st_info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} st_builtin_table_t;



int hsh(st_info_t *, char **);
int find_builtin(st_info_t *);
void find_cmd(st_info_t *);
void fork_cmd(st_info_t *);
int is_cmd(st_info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(st_info_t *, char *, char *);
int loophsh(char **);
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **strtow(char *, char *);
char **strtow2(char *, char);
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);
int interactive(st_info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int _erratoi(char *);
void print_error(st_info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _exit(st_info_t *);
int _cd(st_info_t *);
int _help(st_info_t *);
int _history(st_info_t *);
int _alias(st_info_t *);
ssize_t get_input(st_info_t *);
int _getline(st_info_t *, char **, size_t *);
void sigintHandler(int);
void clear_info(st_info_t *);
void set_info(st_info_t *, char **);
void free_info(st_info_t *, int);
char *_getenv(st_info_t *, const char *);
int _env(st_info_t *);
int _setenv(st_info_t *);
int _unsetenv(st_info_t *);
int populate_env_list(st_info_t *);
char **get_environ(st_info_t *);
int _unsetenv(st_info_t *, char *);
int _setenv(st_info_t *, char *, char *);
char *get_history_file(st_info_t *info);
int write_history(st_info_t *info);
int read_history(st_info_t *info);
int build_history_list(st_info_t *info, char *buf, int linecount);
int renumber_history(st_info_t *info);
st_list_t *add_node(st_list_t **, const char *, int);
st_list_t *add_node_end(st_list_t **, const char *, int);
size_t print_list_str(const st_list_t *);
int delete_node_at_index(st_list_t **, unsigned int);
void free_list(st_list_t **);
size_t list_len(const st_list_t *);
char **list_to_strings(st_list_t *);
size_t print_list(const st_list_t *);
st_list_t *node_starts_with(st_list_t *, char *, char);
ssize_t get_node_index(st_list_t *, st_list_t *);
int is_chain(st_info_t *, char *, size_t *);
void check_chain(st_info_t *, char *, size_t *, size_t, size_t);
int replace_alias(st_info_t *);
int replace_vars(st_info_t *);
int replace_string(char **, char *);

#endif