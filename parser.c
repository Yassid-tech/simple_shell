#include "shell.h"

/**
 * iscmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int iscmd(info_t *info, char *path)
{
struct stat sta;
(void)info;
if (!path || stat(path, &sta))
return (0);
if (sta.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
 * dupchars - duplicates characters
 * @path_str: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *dupchars(char *path_str, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;
for (k = 0, i = start; i < stop; i++)
if (path_str[i] != ':')
buf[k++] = path_str[i];
buf[k] = 0;
return (buf);
}

/**
 * findpath - finds this cmd in the PATH string
 * @info: the info struct
 * @path_str: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *findpath(info_t *info, char *path_str, char *cmd)
{
int i = 0, currpos = 0;
char *path;
if (!path_str)
return (NULL);
if ((_strlen(cmd) > 2) && startswith(cmd, "./"))
{
if (iscmd(info, cmd))
return (cmd);
}
while (1)
{
if (!path_str[i] || path_str[i] == ':')
{
path = dupchars(path_str, currpos, i);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (iscmd(info, path))
return (path);
if (!path_str[i])
break;
currpos = i;
}
i++;
}
return (NULL);
}
