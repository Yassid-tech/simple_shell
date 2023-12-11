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
