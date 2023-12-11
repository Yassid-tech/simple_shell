Memo's part
emacs _atoi.c

#include "shell.h"


/**

 * interactive - returns true if shell is interactive mode

 * @info: struct address

 *

 * Return: 1 if interactive mode, 0 otherwise

 */

int interactive(info_t *infor)

{

return (isatty(STDIN_FILENO) && infor->readfd <= 2);

}


/**

 * isdelim - checks if character is a delimeter

 * @c: the char to check

 * @delim: the delimeter string

 * Return: 1 if true, 0 if false

 */

int isdelim(char c, char *delime)

{

while (*delime)

if (*delime++ == c)

return (1);

return (0);

}


/**

 *_isalpha - checks for alphabetic character

 *@c: The character to input

 *Return: 1 if c is alphabetic, 0 otherwise

 */


int _isalpha(int c)

{

if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))

return (1);

else

return (0);

}


/**

 *_atoi - converts a string to an integer

 *@s: the string to be converted

 *Return: 0 if no numbers in string, converted number otherwise

 */


int _atoi(char *s)

{

int j, sign = 1, flag = 0, output;

unsigned int result = 0;

for (j = 0;  s[j] != '\0' && flag != 2; j++)

{

if (s[j] == '-')

sign *= -1;

if (s[j] >= '0' && s[j] <= '9')

{

flag = 1;

result *= 10;

result += (s[j] - '0');

}

else if (flag == 1)

flag = 2;

}

if (sign == -1)

output = -result;

else

output = result;

return (output);

}



chmod u+x _atoi.c
git add .
git commit -m “Check and Convert a chat to an integer”
git push



—-------------------------------------------------------------------------------------------------------------



emacs builtin.c

#include "shell.h"


/**

 * _myexit - exits the shell

 * @info: Structure containing potential arguments. Used to maintain

 *          constant function prototype.

 *  Return: exits with a given exit status

 *         (0) if info.argv[0] != "exit"

 */

int _myexit(info_t *info)

{

int exitcheck;

if (info->argv[1])  /* If there is an exit arguement */

{

exitcheck = _erratoi(info->argv[1]);

if (exitcheck == -1)

{

info->status = 2;

printerror(info, "Illegal number: ");

_eputs(info->argv[1]);

_eputchar('\n');

return (1);

}

info->err_num = _erratoi(info->argv[1]);

return (-2);

}

info->err_num = -1;

return (-2);

}

/**

 * _mycd - changes the current directory of the process

 * @info: Structure containing potential arguments. Used to maintain

 *          constant function prototype.

 *  Return: Always 0

 */

int _mycd(info_t *info)

{

char *s, *dir, buffer[1024];

int chdirret;

s = getcwd(buffer, 1024);

if (!s)

_puts("TODO: >>getcwd failure emsg here<<\n");

if (!info->argv[1])

{

dir = _getenv(info, "HOME=");

if (!dir)

chdirret = /* TODO: what should this be? */

chdir((dir = _getenv(info, "PWD=")) ? dir : "/");

else

chdirret = chdir(dir);

}

else if (_strcmp(info->argv[1], "-") == 0)

{

if (!_getenv(info, "OLDPWD="))

{

_puts(s);

_putchar('\n');

return (1);

}

_puts(_getenv(info, "OLDPWD=")), _putchar('\n');

chdirret = /* TODO: what should this be? */

chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");

}

else

chdirret = chdir(info->argv[1]);

if (chdirret == -1)

{

printerror(info, "can't cd to ");

_eputs(info->argv[1]), _eputchar('\n');

}

else

{

_setenv(info, "OLDPWD", _getenv(info, "PWD="));

_setenv(info, "PWD", getcwd(buffer, 1024));

}

return (0);

}


/**

 * _myhelp - changes the current directory of the process

 * @info: Structure containing potential arguments. Used to maintain

 *          constant function prototype.

 *  Return: Always 0

 */

int _myhelp(info_t *info)

{

char **arg_array;

arg_array = info->argv;

_puts("help call works. Function not yet implemented \n");

if (0)

_puts(*arg_array); /* temp att_unused workaround */

return (0);

}



chmod u+x builtin.c
git add .
git commit -m “Exit shell”
git push


—------------------------------------------------------------------------------------------------------------------------



emacs builtin1.c

#include "shell.h"


/**

 * _myhistory - displays the history list, one command by line, preceded

 *              with line numbers, starting at 0.

 * @info: Structure containing potential arguments. Used to maintain

 *        constant function prototype.

 *  Return: Always 0

 */

int _myhistory(info_t *info)

{

printlist(info->history);

return (0);

}


/**

 * unsetalias - sets alias to string

 * @info: parameter struct

 * @str: the string alias

 *

 * Return: Always 0 on success, 1 on error

 */

int unsetalias(info_t *info, char *str)

{

char *p, c;

int ret;

p = _strchr(str, '=');

if (!p)

return (1);

c = *p;

*p = 0;

ret = deletenodeatindex(&(info->alias),

getnodeindex(info->alias, nodestartswith(info->alias, str, -1)));

*p = c;

return (ret);

}


/**

 * setalias - sets alias to string

 * @info: parameter struct

 * @str: the string alias

 *

 * Return: Always 0 on success, 1 on error

 */

int setalias(info_t *info, char *str)

{

char *p;

p = _strchr(str, '=');

if (!p)

return (1);

if (!*++p)

return (unsetalias(info, str));

unsetalias(info, str);

return (addnodeend(&(info->alias), str, 0) == NULL);

}


/**

 * printalias - prints an alias string

 * @node: the alias node

 *

 * Return: Always 0 on success, 1 on error

 */

int printalias(list_t *node)

{

char *p = NULL, *a = NULL;

if (node)

{

p = _strchr(node->str, '=');

for (a = node->str; a <= p; a++)

_putchar(*a);

_putchar('\'');

_puts(p + 1);

_puts("'\n");

return (0);

}

return (1);

}


/**

 * _myalias - mimics the alias builtin

 * @info: Structure containing potential arguments. Used to maintain

 *          constant function prototype.

 *  Return: Always 0

 */

int _myalias(info_t *info)

{

int i = 0;

char *p = NULL;

list_t *node = NULL;

if (info->argc == 1)

{

node = info->alias;

while (node)

{

printalias(node);

node = node->next;

}

return (0);

}

for (i = 1; info->argv[i]; i++)

{

p = _strchr(info->argv[i], '=');

if (p)

setalias(info, info->argv[i]);

else

printalias(nodestartswith(info->alias, info->argv[i], '='));

}

return (0);

}



chmod u+x builtin1.c
git add .
git commit -m “Display history list in one command”
git push


—------------------------------------------------------------------------------------------------------------------------


emacs environ.c


#include "shell.h"


/**

 * _myenv - prints the current environment

 * @info: Structure containing potential arguments. Used to maintain

 *          constant function prototype.

 * Return: Always 0

 */

int _myenv(info_t *info)

{

printliststr(info->env);

return (0);

}


/**

 * _getenv - gets the value of an environ variable

 * @info: Structure containing potential arguments. Used to maintain

 * @name: env var name

 *

 * Return: the value

 */

char *_getenv(info_t *info, const char *name)

{

list_t *node = info->env;

char *p;

while (node)

{

p = startswith(node->str, name);

if (p && *p)

return (p);

node = node->next;

}

return (NULL);

}


/**

 * _mysetenv - Initialize a new environment variable,

 *             or modify an existing one

 * @info: Structure containing potential arguments. Used to maintain

 *        constant function prototype.

 *  Return: Always 0

 */

int _mysetenv(info_t *info)

{

if (info->argc != 3)

{

_eputs("Incorrect number of arguments\n");

return (1);

}

if (_setenv(info, info->argv[1], info->argv[2]))

return (0);

return (1);

}


/**

 * _myunsetenv - Remove an environment variable

 * @info: Structure containing potential arguments. Used to maintain

 *        constant function prototype.

 *  Return: Always 0

 */

int _myunsetenv(info_t *info)

{

int i;

if (info->argc == 1)

{

_eputs("Too few arguements.\n");

return (1);

}

for (i = 1; i <= info->argc; i++)

_unsetenv(info, info->argv[i]);

return (0);

}


/**

 * populateenvlist - populates env linked list

 * @info: Structure containing potential arguments. Used to maintain

 *          constant function prototype.

 * Return: Always 0

 */

int populateenvlist(info_t *info)

{

list_t *node = NULL;

size_t i;

for (i = 0; environ[i]; i++)

addnodeend(&node, environ[i], 0);

info->env = node;

return (0);

}



chmod u+x environ.c
git add .
git commit -m “Print the current environment”
git push


—------------------------------------------------------------------------------------------------------------------------



emacs errors.c

#include "shell.h"


/**

 *_eputs - prints an input string

 * @str: the string to be printed

 *

 * Return: Nothing

 */

void _eputs(char *str)

{

int i = 0;

if (!str)

return;

while (str[i] != '\0')

{

_eputchar(str[i]);

i++;

}

}


/**

 * _eputchar - writes the character c to stderr

 * @c: The character to print

 *

 * Return: On success 1.

 * On error, -1 is returned, and errno is set appropriately.

 */

int _eputchar(char c)

{

static int i;

static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)

{

write(2, buf, i);

i = 0;

}

if (c != BUF_FLUSH)

buf[i++] = c;

return (1);

}


/**

 * _putfd - writes the character c to given fd

 * @c: The character to print

 * @fd: The filedescriptor to write to

 *

 * Return: On success 1.

 * On error, -1 is returned, and errno is set appropriately.

 */

int _putfd(char c, int fd)

{

static int i;

static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)

{

write(fd, buf, i);

i = 0;

}

if (c != BUF_FLUSH)

buf[i++] = c;

return (1);

}


/**

 *_putsfd - prints an input string

 * @str: the string to be printed

 * @fd: the filedescriptor to write to

 *

 * Return: the number of chars put

 */

int _putsfd(char *str, int fd)

{

int i = 0;

if (!str)

return (0);

while (*str)

{

i += _putfd(*str++, fd);

}

return (i);

}



chmod u+x errors.c
git add .
git commit -m “Print Strings”
git push


—------------------------------------------------------------------------------------------------------------------------


emacs errors1.c

#include "shell.h"


/**

 * _erratoi - converts a string to an integer

 * @s: the string to be converted

 * Return: 0 if no numbers in string, converted number otherwise

 *       -1 on error

 */

int _erratoi(char *s)

{

int i = 0;

unsigned long int result = 0;

if (*s == '+')

s++;  /* TODO: why does this make main return 255? */

for (i = 0;  s[i] != '\0'; i++)

{

if (s[i] >= '0' && s[i] <= '9')

{

result *= 10;

result += (s[i] - '0');

if (result > INT_MAX)

return (-1);

}

else

return (-1);

}

return (result);

}


/**

 * printerror - prints an error message

 * @info: the parameter & return info struct

 * @estr: string containing specified error type

 * Return: 0 if no numbers in string, converted number otherwise

 *        -1 if error

 */

void printerror(info_t *info, char *estr)

{

_eputs(info->fname);

_eputs(": ");

printd(info->linecount, STDERR_FILENO);

_eputs(": ");

_eputs(info->argv[0]);

_eputs(": ");

_eputs(estr);

}


/**

 * printd - function prints a decimal number (base 10)

 * @input: the input

 * @fd: the filedescriptor to write to

 *

 * Return: number of characters printed

 */

int printd(int input, int fd)

{

int (*__putchar)(char) = _putchar;

int i, count = 0;

unsigned int _abs_, current;

if (fd == STDERR_FILENO)

__putchar = _eputchar;

if (input < 0)

{

_abs_ = -input;

__putchar('-');

count++;

}

else

_abs_ = input;

current = _abs_;

for (i = 1000000000; i > 1; i /= 10)

{

if (_abs_ / i)

{

__putchar('0' + current / i);

count++;

}

current %= i;

}

__putchar('0' + current);

count++;

return (count);

}


/**

 * convertnumber - converter function, a clone of iota

 * @num: number

 * @base: base

 * @flags: argument flags

 *

 * Return: string

 */

char *convertnumber(long int num, int base, int flags)

{

static char *array;

static char buffer[50];

char sign = 0;

char *ptr;

unsigned long n = num;

if (!(flags & CONVERT_UNSIGNED) && num < 0)

{

n = -num;

sign = '-';

}

array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";

ptr = &buffer[49];

*ptr = '\0';

do

{

*--ptr = array[n % base];

n /= base;

} while (n != 0);

if (sign)

*--ptr = sign;

return (ptr);

}


/**

 * removecomments - function replaces first instance of '#' with '\0'

 * @buf: address of the string to modify

 *

 * Return: Always 0;

 */

void removecomments(char *buf)

{

int i;

for (i = 0; buf[i] != '\0'; i++)

if (buf[i] == '#' && (!i || buf[i - 1] == ' '))

{

buf[i] = '\0';

break;

}

}


chmod u+x errors1.c
git add .
git commit -m “Print errors, convert numbers, and remove comments”
git push


—------------------------------------------------------------------------------------------------------------------------


emacs exits.c

#include "shell.h"


/**

 **_strncpy - copies a string

 *@dest: the destination string to be copied to

 *@src: the source string

 *@n: the amount of characters to be copied

 *Return: the concatenated string

 */

char *_strncpy(char *dest, char *src, int n)

{

int i, j;

char *s = dest;

i = 0;

while (src[i] != '\0' && i < n - 1)

{

dest[i] = src[i];

i++;

}

if (i < n)

{

j = i;

while (j < n)

{

dest[j] = '\0';

j++;

}

}

return (s);

}


/**

 **_strncat - concatenates two strings

 *@dest: the first string

 *@src: the second string

 *@n: the amount of bytes to be maximally used

 *Return: the concatenated string

 */

char *_strncat(char *dest, char *src, int n)

{

int i, j;

char *s = dest;

i = 0;

j = 0;

while (dest[i] != '\0')

i++;

while (src[j] != '\0' && j < n)

{

dest[i] = src[j];

i++;

j++;

}

if (j < n)

dest[i] = '\0';

return (s);

}


/**

 **_strchr - locates a character in a string

 *@s: the string to be parsed

 *@c: the character to look for

 *Return: (s) a pointer to the memory area s

 */

char *_strchr(char *s, char c)

{

do {

if (*s == c)

return (s);

} while (*s++ != '\0');

return (NULL);

}



chmod u+x exits.c
git add .
git commit -m “Copy String”
git push

—------------------------------------------------------------------------------------------------------------------------


emacs getLine.c

#include "shell.h"


/**

 * inputbuf - buffers chained commands

 * @info: parameter struct

 * @buf: address of buffer

 * @len: address of len var

 *

 * Return: bytes read

 */

ssize_t inputbuf(info_t *info, char **buf, size_t *len)

{

ssize_t r = 0;

size_t len_p = 0;

if (!*len) /* if nothing left in the buffer, fill it */

{

/*befree((void **)info->cmd_buf);*/

free(*buf);

*buf = NULL;

signal(SIGINT, sigintHandler);

#if USE_GETLINE

r = getline(buf, &len_p, stdin);

#else

r = _getline(info, buf, &len_p);

#endif

if (r > 0)

{

if ((*buf)[r - 1] == '\n')

{

(*buf)[r - 1] = '\0'; /* remove trailing newline */

r--;

}

info->linecount_flag = 1;

removecomments(*buf);

buildhistorylist(info, *buf, info->histcount++);

/* if (_strchr(*buf, ';')) is this a command chain? */

{

*len = r;

info->cmd_buf = buf;

}

}

}

return (r);

}


/**

 * getinput - gets a line minus the newline

 * @info: parameter struct

 *

 * Return: bytes read

 */

ssize_t getinput(info_t *info)

{

static char *buf; /* the ';' command chain buffer */

static size_t i, j, len;

ssize_t r = 0;

char **buf_p = &(info->arg), *p;

_putchar(BUF_FLUSH);

r = inputbuf(info, &buf, &len);

if (r == -1) /* EOF */

return (-1);

if (len)        /* we have commands left in the chain buffer */

{

j = i; /* init new iterator to current buf position */

p = buf + i; /* get pointer for return */

checkchain(info, buf, &j, i, len);

while (j < len) /* iterate to semicolon or end */

{

if (ischain(info, buf, &j))

break;

j++;

}

i = j + 1; /* increment past nulled ';'' */

if (i >= len) /* reached end of buffer? */

{

i = len = 0; /* reset position and length */

info->cmd_buf_type = CMD_NORM;

}

*buf_p = p; /* pass back pointer to current command position */

return (_strlen(p)); /* return length of current command */

}

*buf_p = buf; /* else not a chain, pass back buffer from _getline() */

return (r); /* return length of buffer from _getline() */

}


/**

 * readbuf - reads a buffer

 * @info: parameter struct

 * @buf: buffer

 * @i: size

 *

 * Return: r

 */

ssize_t readbuf(info_t *info, char *buf, size_t *i)

{

ssize_t r = 0;

if (*i)

return (0);

r = read(info->readfd, buf, READBUF_SIZE);

if (r >= 0)

*i = r;

return (r);

}


/**

 * _getline - gets the next line of input from STDIN

 * @info: parameter struct

 * @ptr: address of pointer to buffer, preallocated or NULL

 * @length: size of preallocated ptr buffer if not NULL

 *

 * Return: s

 */

int _getline(info_t *info, char **ptr, size_t *length)

{

static char buf[READBUF_SIZE];

static size_t i, len;

size_t k;

ssize_t r = 0, s = 0;

char *p = NULL, *new_p = NULL, *c;

p = *ptr;

if (p && length)

s = *length;

if (i == len)

i = len = 0;

r = readbuf(info, buf, &len);

if (r == -1 || (r == 0 && len == 0))

return (-1);

c = _strchr(buf + i, '\n');

k = c ? 1 + (unsigned int)(c - buf) : len;

new_p = _realloc(p, s, s ? s + k : k + 1);

if (!new_p) /* MALLOC FAILURE! */

return (p ? free(p), -1 : -1);

if (s)

_strncat(new_p, buf + i, k - i);

else

_strncpy(new_p, buf + i, k - i + 1);

s += k - i;

i = k;

p = new_p;

if (length)

*length = s;

*ptr = p;

return (s);

}


/**

 * sigintHandler - blocks ctrl-C

 * @sig_num: the signal number

 *

 * Return: void

 */

void sigintHandler(__attribute__((unused))int sig_num)

{

_puts("\n");

_puts("$ ");

_putchar(BUF_FLUSH);

}
