#ifndef MY_SHELL_H
#define MY_SHELL_H

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

/* for cvt_num() */
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
 * @num_par: the number field
 * @_str: a string
 * @next: points to the next _nod
 */
typedef struct liststr
{
	int num_par;
	char *_str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @file_path: a string file_path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()conv_string
 * @linecount_flag: if on count this line of input_par
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history _nod
 * @alias: the alias _nod
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @buff_typ: CMD_type ||, &&, ;
 * @readfd: the filed_para from which to read line input_par
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *file_path;
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
	int buff_typ; /* CMD_type ||, &&, ; */
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


/* toem_shloop._ichar */
int func_hsh(info_t *, char **);
int _fbuilt(info_t *);
void func_find_cmd(info_t *);
void func_fork_cmd(info_t *);

/* toem_parser._ichar */
int i_exec(info_t *, char *);
char *func_dup_chars(char *, int, int);
char *f_path(info_t *, char *, char *);

/* loophsh._ichar */
int loophsh(char **);

/* toem_errors._ichar */
void my_eputs_func(char *);
int my_eputchar_func(char);
int func_putfd(char _ichar, int filed_para);
int my_putsfd(char *_str, int filed_para);

/* toem_string._ichar */
int _strlen(char *);
int func__strcmp(char *, char *);
char *func_starts_with(const char *, const char *);
char *func_strcat(char *, char *);

/* toem_string1._ichar */
char *func_strcpy(char *, char *);
char *func_strdup(const char *);
void func_puts(char *);
int func_putchar(char);

/* toem_exits._ichar */
char *my_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer._ichar */
char **strtow_func(char *, char *);
char **strtow2(char *, char);

/* toem_realloc._ichar */
char *func_memset(char *, char, unsigned int);
void func_ffree(char **);
void *func__realloc(void *, unsigned int, unsigned int);

/* toem_memory._ichar */
int func_bfree(void **);

/* toem_atoi._ichar */
int _ifunc(info_t *);
int dfunc(char, char *);
int _ialpha(int);
int _atoi(char *);

/* toem_errors1._ichar */
int my_erratoi_func(char *);
void print_error_func(info_t *, char *);
int myprint_dec(int, int);
char *cvt_num(long int, int, int);
void func_remove_comments(char *);

/* toem_builtin._ichar */
int my_exit_func(info_t *);
int my_cd_func(info_t *);
int my_help_func(info_t *);

/* toem_builtin1._ichar */
int _histf(info_t *);
int my_alias_func(info_t *);

/*toem_getline._ichar */
ssize_t _ginput(info_t *);
int _getline(info_t *, char **, size_t *);
void _sigintHandler(int);

/* toem_getinfo._ichar */
void _cinfo(info_t *);
void _sinfo(info_t *, char **);
void _finfo(info_t *, int);

/* toem_environ._ichar */
char *g_env(info_t *, const char *);
int my_env_func(info_t *);
int set_myenv_func(info_t *);
int my_unsetenv_func(info_t *);
int populate_env_list(info_t *);

/* toem_getenv._ichar */
char **get_env(info_t *);
int my_unsetenv_func(info_t *, char *);
int _setenv_func(info_t *, char *, char *);

/* toem_history._ichar */
char *_hfile(info_t *i_strc);
int w_hist(info_t *i_strc);
int _rhist(info_t *i_strc);
int _hlist(info_t *i_strc, char *_buff, int linecount);
int func_renumber_history(info_t *i_strc);

/* toem_lists._ichar */
list_t *func_add_node(list_t **, const char *, int);
list_t *add_node_end_func(list_t **, const char *, int);
size_t print_list_str_func(const list_t *);
int del_index(list_t **, unsigned int);
void func_free_list(list_t **);

/* toem_lists1._ichar */
size_t list_len_func(const list_t *);
char **func_list_to_strings(list_t *);
size_t p_list(const list_t *);
list_t *f_stw(list_t *, char *, char);
ssize_t g_index(list_t *, list_t *);

/* toem_vars._ichar */
int i_chn(info_t *, char *, size_t *);
void c_chn(info_t *, char *, size_t *, size_t, size_t);
int rep_ali(info_t *);
int rep_var(info_t *);
int rep_str(char **, char *);

#endif
