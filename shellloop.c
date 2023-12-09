#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter and return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 if success, 1 if error, or error code
 */
int hsh(info_t *info, char **av)
{
ssize_t s = 0;
int built_ret = 0;
while (s != -1 && built_ret != -2)
{
clearinfo(info);
if (interactive(info))
_puts("$ ");
_eputchar(BUF_FLUSH);
s = getinput(info);
if (s != -1)
{
setinfo(info, av);
built_ret = findbuilt(info);
if (built_ret == -1)
findcmd(info);
}
else if (interactive(info))
_putchar('\n');
freeinfo(info, 0);
}
writehistory(info);
freeinfo(info, 1);
if (!interactive(info) && info->status)
exit(info->status);
if (built_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (built_ret);
}

/**
 * findbuilt - finds a built command
 * @info: the parameter, return info struct
 *
 * Return: -1 if built not found,
 *			0 if built executed successfully,
 *			1 if built found but not successful,
 *			-2 if built signals exit()
 */
int findbuilt(info_t *info)
{
int j, builtinret = -1;
builtin_table builtintbl[] = {
{"exit", _myexit},
{"env", _myenv},
{"help", _myhelp},
{"history", _myhistory},
{"setenv", _mysetenv},
{"unsetenv", _myunsetenv},
{"cd", _mycd},
{"alias", _myalias},
{NULL, NULL}
};
for (j = 0; builtintbl[j].type; j++)
if (_strcmp(info->argv[0], builtintbl[j].type) == 0)
{
info->linecount++;
builtinret = builtintbl[j].func(info);
break;
}
return (builtinret);
}

/**
 * findcmd - finds a command in PATH
 * @info: the parameter, return info struct
 *
 * Return: void
 */
void findcmd(info_t *info)
{
char *path = NULL;
int j, k;
info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->linecount++;
info->linecount_flag = 0;
}
for (j = 0, k = 0; info->arg[j]; j++)
if (!isdelim(info->arg[j], " \t\n"))
k++;
if (!k)
return;
path = findpath(info, _getenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
forkcmd(info);
}
else
{
if ((interactive(info) || _getenv(info, "PATH=")
|| info->argv[0][0] == '/') && iscmd(info, info->argv[0]))
forkcmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
printerror(info, "not found\n");
}
}
}

/**
 * forkcmd - forks a an exec thread to run cmd
 * @info: the parameter, return info struct
 *
 * Return: void
 */
void forkcmd(info_t *info)
{
pid_t childpid;
childpid = fork();
if (childpid == -1)
{
/* TODO: PUT ERROR FUNCTION */
perror("Error:");
return;
}
if (childpid == 0)
{
if (execve(info->path, info->argv, getenviron(info)) == -1)
{
freeinfo(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
/* TODO: PUT ERROR FUNCTION */
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
printerror(info, "Permission denied\n");
}
}
}
