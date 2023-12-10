#include "shell.h"

/**
 * addnode - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *addnode(list_t **head, const char *str, int num)
{
list_t *newhead;
if (!head)
return (NULL);
newhead = malloc(sizeof(list_t));
if (!newhead)
return (NULL);
_memset((void *)newhead, 0, sizeof(list_t));
newhead->num = num;
if (str)
{
newhead->str = _strdup(str);
if (!newhead->str)
{
free(newhead);
return (NULL);
}
}
newhead->next = *head;
*head = newhead;
return (newhead);
}

/**
 * addnodeend - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *addnodeend(list_t **head, const char *str, int num)
{
list_t *newnode, *node;
if (!head)
return (NULL);
node = *head;
newnode = malloc(sizeof(list_t));
if (!newnode)
return (NULL);
_memset((void *)newnode, 0, sizeof(list_t));
newnode->num = num;
if (str)
{
newnode->str = _strdup(str);
if (!newnode->str)
{
free(newnode);
return (NULL);
}
}
if (node)
{
while (node->next)
node = node->next;
node->next = newnode;
}
else
*head = newnode;
return (newnode);
}

/**
 * printliststr - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t printliststr(const list_t *h)
{
size_t j = 0;
while (h)
{
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
j++;
}
return (j);
}

/**
 * deletenodeatindex - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int deletenodeatindex(list_t **head, unsigned int index)
{
list_t *node, *prevnode;
unsigned int j = 0;
if (!head || !*head)
return (0);
if (!index)
{
node = *head;
*head = (*head)->next;
free(node->str);
free(node);
return (1);
}
node = *head;
while (node)
{
if (j == index)
{
prevnode->next = node->next;
free(node->str);
free(node);
return (1);
}
j++;
prevnode = node;
node = node->next;
}
return (0);
}

/**
 * freelist - free all the nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void freelist(list_t **head_ptr)
{
list_t *node, *nextnode, *head;
if (!head_ptr || !*head_ptr)
return;
head = *head_ptr;
node = head;
while (node)
{
nextnode = node->next;
free(node->str);
free(node);
node = nextnode;
}
*head_ptr = NULL;
}
