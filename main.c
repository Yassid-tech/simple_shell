#include "shell.h"

/**
 * main - beginning point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 if success, 1 if error
 */
int main(int ac, char **av)
{
info_t info[] = { INFO_INIT };
int fda = 2;
asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (fda)
: "r" (fda));
if (ac == 2)
{
fda = open(av[1], O_RDONLY);
if (fda == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
_eputs(av[0]);
_eputs(": 0: Can't open ");
_eputs(av[1]);
_eputchar('\n');
_eputchar(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
info->readfd = fda;
}
populateenvlist(info);
readhistory(info);
hsh(info, av);
return (EXIT_SUCCESS);
}
