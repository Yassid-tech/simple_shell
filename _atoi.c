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
