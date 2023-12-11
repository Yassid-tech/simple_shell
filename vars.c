#include "shell.h"


/**

 * ischain - test if current char in buffer is a chain delimeter

 * @info: the parameter struct

 * @buf: the char buffer

 * @p: address of current position in buf

 *

 * Return: 1 if chain delimeter, 0 otherwise

 */

int ischain(info_t *info, char *buf, size_t *p)

{

size_t j = *p;

if (buf[j] == '|' && buf[j + 1] == '|')

{

buf[j] = 0;

j++;

info->cmd_buf_type = CMD_OR;

}

else if (buf[j] == '&' && buf[j + 1] == '&')

{

buf[j] = 0;

j++;

info->cmd_buf_type = CMD_AND;

}

else if (buf[j] == ';') /* found end of this command */

{

buf[j] = 0; /* replace semicolon with null */

info->cmd_buf_type = CMD_CHAIN;

}

else

return (0);

*p = j;

return (1);

}


/**

 * checkchain - checks we should continue chaining based on last status

 * @info: the parameter struct

 * @buf: the char buffer

 * @p: address of current position in buf

 * @i: starting position in buf

 * @len: length of buf

 *

 * Return: Void

 */

void checkchain(info_t *info, char *buf, size_t *p, size_t j, size_t len)

{

size_t j = *p;

if (info->cmd_buf_type == CMD_AND)

{

if (info->status)

{

buf[j] = 0;

j = len;

}

}

if (info->cmd_buf_type == CMD_OR)

{

if (!info->status)

{

buf[j] = 0;

j = len;

}

}

*p = j;

}


/**

 * replacealias - replaces an aliases in the tokenized string

 * @info: the parameter struct

 *

 * Return: 1 if replaced, 0 otherwise

 */

int replacealias(info_t *info)

{

int j;

list_t *node;

char *p;

for (j = 0; j < 10; j++)

{

node = nodestartswith(info->alias, info->argv[0], '=');

if (!node)

return (0);

free(info->argv[0]);

p = _strchr(node->str, '=');

if (!p)

return (0);

p = _strdup(p + 1);

if (!p)

return (0);

info->argv[0] = p;

}

return (1);

}


/**

 * replacevars - replaces vars in the tokenized string

 * @info: the parameter struct

 *

 * Return: 1 if replaced, 0 otherwise

 */

int replacevars(info_t *info)

{

int i = 0;

list_t *node;

for (i = 0; info->argv[i]; i++)

{

if (info->argv[i][0] != '$' || !info->argv[i][1])

continue;

if (!_strcmp(info->argv[i], "$?"))

{

replacestring(&(info->argv[i]),

_strdup(convertnumber(info->status, 10, 0)));

continue;

}

if (!_strcmp(info->argv[i], "$$"))

{

replacestring(&(info->argv[i]),

_strdup(convertnumber(getpid(), 10, 0)));

continue;

}

node = nodestartswith(info->env, &info->argv[i][1], '=');

if (node)

{

replacestring(&(info->argv[i]),

_strdup(_strchr(node->str, '=') + 1));

continue;

}

replacestring(&info->argv[i], _strdup(""));

}

return (0);

}


/**

 * replacestring - replaces string

 * @old: address of old string

 * @new: new string

 *

 * Return: 1 if replaced, 0 otherwise

 */

int replacestring(char **old, char *new)

{

free(*old);

*old = new;

return (1);

}
