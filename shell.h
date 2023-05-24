#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>

/*It is used for write/read buffers */
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1

/*uses for converting numbers () */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
/* one when the using systems getline () */
#define USE_STRTOK 0
#define USE_GETLINE 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr-singly linke the list
 * @num: the numbers field
 * @str: the string
 * @next: point to be the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;
/**
 * struct passinfo - contains pseudo_arguements to be pass into a function,
 * allowing uniform prototype fors function pointers struct
 * @arg: a string generated from getlines contained arguements
 * @argv:an array of strings generateing from arg
 * @path: a string path for the current command
 * @argc: the argument counts
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: when on count this line of input
 * @fname: the program filenames
 * @env: linked listed local copy of environ
 * @environ: customing modified copy of environ from LL env
 * @history: the historytobe node
 * @alias: the alias was noded
 * @env_changed: on when environ were changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointers t beo cmd_buf, on when chaining
 * @cmd_buf_type: CMD_types ||, &&, ;
 * @readfd: the fd from which to be reading line input
 * @histcount: the history lines numbers counted
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
} info_t;

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
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem-parsers.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* loophsh.c code */
int loophsh(char **);

/* toem-error.c code */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem-string.c code */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem-string one0.c code */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* Toem-exited.c code */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* Toem-tokenizer.c code */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* Toem-realloc.c code */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* Toem-memory.c code */
int bfree(void **);

/* Toem-atoi.c code */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* Toem-errors one.c code */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* Toem-builtin.c code */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* Toem-builtin one.c code */
int _myhistory(info_t *);
int _myalias(info_t *);

/*Toem-getline.c code */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* Toem-getinfo.c code */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* Toem-environ.c code */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);


/* Toem-getenv.c code */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* Toem-history.c code */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* Toem-lists.c code */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* Toem-lists one.c code */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* Toem-vars.c code */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
