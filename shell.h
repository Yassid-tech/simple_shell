#ifndef SHELL_H
#define SHELL_H

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

#define READBUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

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
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
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
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;


int hsh(info_t *, char **);
int findbuilt(info_t *);
void findcmd(info_t *);
void forkcmd(info_t *);

int iscmd(info_t *, char *);
char *dupchars(char *, int, int);
char *findpath(info_t *, char *, char *);

int loophsh(char **);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *startswith(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **strtw(char *, char *);
char **strtw1(char *, char);

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int befree(void **);

int interactive(info_t *);
int isdelim(char, char *);
int _isalpha(int);
int _atoi(char *);

int _erratoi(char *);
void printerror(info_t *, char *);
int printd(int, int);
char *convertnumber(long int, int, int);
void removecomments(char *);

int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

int _myhistory(info_t *);
int _myalias(info_t *);

ssize_t getinput(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

void clearinfo(info_t *);
void setinfo(info_t *, char **);
void freeinfo(info_t *, int);

char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populateenvlist(info_t *);

char **getenviron(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

char *gethistoryfile(info_t *info);
int writehistory(info_t *info);
int readhistory(info_t *info);
int buildhistorylist(info_t *info, char *buf, int linecount);
int renumberhistory(info_t *info);

list_t *addnode(list_t **, const char *, int);
list_t *addnodeend(list_t **, const char *, int);
size_t printliststr(const list_t *);
int deletenodeatindex(list_t **, unsigned int);
void freelist(list_t **);

size_t listlen(const list_t *);
char **listtostrings(list_t *);
size_t printlist(const list_t *);
list_t *node_startswith(list_t *, char *, char);
ssize_t getnodeindex(list_t *, list_t *);

int ischain(info_t *, char *, size_t *);
void checkchain(info_t *, char *, size_t *, size_t, size_t);
int replacealias(info_t *);
int replacevars(info_t *);
int replacestring(char **, char *);

#endif
