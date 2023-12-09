#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
unsigned int j;
for (j = 0; j < n; j++)
s[j] = b;
return (s);
}

/**
 * ffree - frees a string of strings
 * @p: string of strings
 */
void ffree(char **p)
{
char **as = p;
if (!p)
return;
while (*p)
free(*p++);
free(as);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @oldsize: byte size of previous block
 * @newsize: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int oldsize, unsigned int newsize)
{
char *po;
if (!ptr)
return (malloc(newsize));
if (!newsize)
return (free(ptr), NULL);
if (newsize == oldsize)
return (ptr);
po = malloc(newsize);
if (!po)
return (NULL);
oldsize = oldsize < newsize ? oldsize : newsize;
while (oldsize--)
po[oldsize] = ((char *)ptr)[oldsize];
free(ptr);
return (po);
}
