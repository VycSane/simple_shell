#include "_strings.h"

/**
 * _strcmp - compares the equality of two strings
 * @s1: the string the result is relative to
 * @s2: the string s1 is compared to
 * Return: 0 if s1 and s2 are equal
 * 1 if s1 > s2
 * -1 if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	size_t i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] < s2[i])
			return (-1);
		if (s1[i] > s2[i])
			return (1);
		i++;
	}
	if (s1[i] == '\0' && s2[i] != '\0')
		return (-1);
	if (s1[i] != '\0' && s2[i] == '\0')
		return (1);
	return (0);
}
