#include "_strings.h"
#include "_getline.h"
#include "_shell_utils.h"
#include "_allocs.h"

/**
 * _getline - gets a line of string from a stream
 * @lineptr: pointer to the buffer for storing the line
 * @size: current size of the buffer memory
 * @stream: the FILE stream to read from
 *
 * Return: the total length of string read
 */
ssize_t _getline(char **lineptr, size_t *size, FILE *stream)
{
	ssize_t len = 0, curr_pos = 0;
	size_t block_size = 100 * sizeof(char), bytesize = block_size - 1;
	char *buff;
	int fd = _fileno(stream);

	if (fd == -1)
		return (-1);
	if (*lineptr == NULL)
	{
		buff = malloc(block_size);
		exit_on_alloc_fail(buff, EXIT_FAILURE);
	}
	while ((len = read(fd, (buff + curr_pos), bytesize)) > 1)
	{
		if (len >= 0)
			curr_pos += len;
		if (buff[curr_pos - 1] == '\n')
		{
			buff[curr_pos] = '\0';
			break;
		}
		else
		{
			block_size += (sizeof(char) * bytesize);
			buff = _realloc(buff, block_size);
			exit_on_alloc_fail(buff, EXIT_FAILURE);
		}
	}
	if (curr_pos == 0)
	{
		buff[1] = '\0';
		curr_pos++;
	}
	copy_and_free(buff, lineptr, size, block_size);
	return (curr_pos);
}
/**
 * copy_and_free - handles memory of the lineptr
 * @buff: the source buffer
 * @lineptr: pointer to the destination buffer
 * @size: size of the user generated memory block
 * @newsize: size of the string copied
 */
void copy_and_free(char *buff, char **lineptr, size_t *size, size_t newsize)
{
	if (*lineptr == NULL)
	{
		update_lineptr(buff, lineptr);
		*size = newsize;
	}

	if (*lineptr != NULL && (*size == 0 || *size < newsize))
	{
		free(*lineptr);
		*lineptr = NULL;
		update_lineptr(buff, lineptr);
		*size = newsize;
	}
	free(buff);
	buff = NULL;
}

/**
 * update_lineptr - copies the source to dest buffer
 * @buff: the source buffer
 * @lineptr: pointer to the destination buffer
 */
void update_lineptr(char *buff, char **lineptr)
{
	size_t len = _strlen(buff);

	*lineptr = malloc((len + 1) * sizeof(char));
	if (*lineptr == NULL)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	_strcpy(*lineptr, buff);
}
