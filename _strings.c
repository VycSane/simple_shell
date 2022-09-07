#include "_strings.h"

/**
* _strlen - it gets the length of a strikng
* @str: the string argument
* Return: the string length
*/
size_t _strlen(char *str)
{
	/* Variable to hold the number of characters in the string */
	size_t count = 0;

	/* Looping through each character of the string */
	while (str[count] != '\0')
		count++;
	return (count);
}

/**
 * _strdup - duplicates the string
 * @str: the string argument
 * Return: a pointer to the string
 */
char *_strdup(char *str)
{
	size_t i = 0;
	char *str_copy;

	str_copy = malloc((_strlen(str) + 1) * sizeof(char));
	if (str_copy == NULL)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	while (str[i] != '\0')
	{
		str_copy[i] = str[i];
		i++;
	}
	str_copy[i] = '\0';
	return (str_copy);
}

/**
 * _strcpy - copies a string
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: the pointer to the copied string
 */
char *_strcpy(char *dest, char *src)
{
	size_t i = 0;

	if (src == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: pointer to the dest buffer
 */
char *_strcat(char *dest, char *src)
{
	size_t i = 0, j = 0;

	j = _strlen(dest);
	while (src[i] != '\0')
	{
		dest[j] = src[i];
		i++, j++;
	}
	dest[j] = '\0';
	return (dest);
}
