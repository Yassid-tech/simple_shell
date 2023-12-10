#include "shell.h"

/**
 * listlen - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t listlen(const list_t *h)
{
size_t j = 0;
while (h)
{
h = h->next;
j++;
}
return (j);
}

/**
 * listtostrings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **listtostrings(list_t *head)
{
list_t *node = head;
size_t i = listlen(head), j;
char **strs;
char *str;
if (!head || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));
if (!strs)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
str = malloc(_strlen(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}
str = _strcpy(str, node->str);
strs[i] = str;
}
strs[i] = NULL;
return (strs);
}


/**
 * printlist - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t printlist(const list_t *h)
{
size_t j = 0;
while (h)
{
_puts(convertnumber(h->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
j++;
}
return (j);
}

/**
 * nodestartswith - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *nodestartswith(list_t *node, char *prefix, char c)
{
char *p = NULL;
while (node)
{
p = startswith(node->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}

/**
 * getnodeindex - get the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t getnodeindex(list_t *head, list_t *node)
{
size_t j = 0;
while (head)
{
if (head == node)
return (j);
head = head->next;
j++;
}
return (-1);
}
