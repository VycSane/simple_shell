#include "_shell_utils.h"
#include "_strings.h"
/**
 * print - prints a string to the specified output
 *
 * @str: the string argument
 * @fd: the file descriptor
 */
void print(char *str, int fd)
{
	write(fd, str, _strlen(str));
}

/**
 * exit_on_alloc_fail - exits when memory allocation fails
 * @block: the memory block
 * @status: the exit status
 */
void exit_on_alloc_fail(void *block, int status)
{
	if (block == NULL)
	{
		perror("Error");
		exit(status);
	}
}
