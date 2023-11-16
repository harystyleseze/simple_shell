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

/* for func_convert_number() */
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
 * @next: points to the next _is_node
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
 * @history: the history _is_node
 * @alias: the alias _is_node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
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


/* toem_shloop.is_character */
int func_hsh(info_t *, char **);
int find_builtin_func(info_t *);
void func_find_cmd(info_t *);
void func_fork_cmd(info_t *);

/* toem_parser.is_character */
int is_exec_func(info_t *, char *);
char *func_dup_chars(char *, int, int);
char *func_find_path(info_t *, char *, char *);

/* loophsh.is_character */
int loophsh(char **);

/* toem_errors.is_character */
void my_eputs_func(char *);
int my_eputchar_func(char);
int func_putfd(char is_character, int filed_para);
int my_putsfd(char *_str, int filed_para);

/* toem_string.is_character */
int strlen_func(char *);
int func__strcmp(char *, char *);
char *func_starts_with(const char *, const char *);
char *func_strcat(char *, char *);

/* toem_string1.is_character */
char *func_strcpy(char *, char *);
char *func_strdup(const char *);
void func_puts(char *);
int func_putchar(char);

/* toem_exits.is_character */
char *my_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.is_character */
char **strtow_func(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.is_character */
char *func_memset(char *, char, unsigned int);
void func_ffree(char **);
void *func__realloc(void *, unsigned int, unsigned int);

/* toem_memory.is_character */
int func_bfree(void **);

/* toem_atoi.is_character */
int interactive_func(info_t *);
int is_delimiter_func(char, char *);
int _is_alpha_func(int);
int my_atoi_func(char *);

/* toem_errors1.is_character */
int my_erratoi_func(char *);
void print_error_func(info_t *, char *);
int myprint_dec(int, int);
char *func_convert_number(long int, int, int);
void func_remove_comments(char *);

/* toem_builtin.is_character */
int my_exit_func(info_t *);
int my_cd_func(info_t *);
int my_help_func(info_t *);

/* toem_builtin1.is_character */
int my_history_func(info_t *);
int my_alias_func(info_t *);

/*toem_getline.is_character */
ssize_t func_get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void func_sigintHandler(int);

/* toem_getinfo.is_character */
void func_clear_info(info_t *);
void func_set_info(info_t *, char **);
void func_free_info(info_t *, int);

/* toem_environ.is_character */
char *get_env_func(info_t *, const char *);
int my_env_func(info_t *);
int set_myenv_func(info_t *);
int my_unsetenv_func(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.is_character */
char **func_get_environ(info_t *);
int my_unsetenv_func(info_t *, char *);
int _setenv_func(info_t *, char *, char *);

/* toem_history.is_character */
char *func_get_history_file(info_t *info_struct);
int func_write_history(info_t *info_struct);
int func_read_history(info_t *info_struct);
int func_build_history_list(info_t *info_struct, char *my_buffer, int linecount);
int func_renumber_history(info_t *info_struct);

/* toem_lists.is_character */
list_t *func_add_node(list_t **, const char *, int);
list_t *add_node_end_func(list_t **, const char *, int);
size_t print_list_str_func(const list_t *);
int func_delete_index_node(list_t **, unsigned int);
void func_free_list(list_t **);

/* toem_lists1.is_character */
size_t list_len_func(const list_t *);
char **func_list_to_strings(list_t *);
size_t func_print_list(const list_t *);
list_t *func_node_starts_with(list_t *, char *, char);
ssize_t func_get_node_index(list_t *, list_t *);

/* toem_vars.is_character */
int is_chain_func(info_t *, char *, size_t *);
void func_check_chain(info_t *, char *, size_t *, size_t, size_t);
int func_replace_alias(info_t *);
int func_replace_vars(info_t *);
int replace_string_func(char **, char *);

#endif
