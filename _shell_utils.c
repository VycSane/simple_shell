#include "_shell_utils.h"
#include "_strings.h"

/**
 * shell_mode - checks if the shell mode is interactive or not
 * @fd: the file descriptor of the stream source
 *
 * Return: true if shell is interactive and false if not interactive
 */
bool shell_mode(int fd)
{
	if (fd < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	if (isatty(fd))
		return (true);
	return (false);
}

/**
 * print_prompt - prints the shell prompt text
 * @str: prompt text to display, if NULL displays default prompt for each mode
 * @shell_mode: the shell mode
 */
void print_prompt(char *str, bool shell_mode)
{
	char *prompt_text;

	/* Decision for the shell prompt text */
	if (str != NULL)
		prompt_text = str;
	else if (shell_mode)
		prompt_text = "($) ";
	else if (!shell_mode)
		prompt_text = "$ ";

	/* Prints the prompt text to the standard output */
	print(prompt_text, STDOUT_FILENO);
}

/**
 * _fileno - gets the file descriptor of a FILE stream
 * @stream: FILE stream
 *
 * Return: -1 on error, or an integer greater than or equal to zero otherwise
 */
int _fileno(FILE *stream)
{
	if (stream == NULL)
		return (-1);
	return (stream->_fileno);
}

/**
 * brk_at_delimiter - replaces specified delimiters with null bytes (\0)
 * @str: the string argument (note: string is modified)
 * @delimiter: list (string) of delimiters
 *
 * Return: the number of tokens that makes up the string, -1 0n error
 */
ssize_t brk_at_delimiter(char *str, char *delimiter)
{
	size_t delimeter_length, str_len, i, j, k = 0;
	ssize_t count = 0;

	if (delimiter == NULL || str == NULL)
		return (-1);
	/* Setting number of delimeters passed & the length of string */
	delimeter_length = _strlen(delimiter);
	str_len = _strlen(str);
	/* Looping through the duplicated string */
	for (i = 0; i < str_len; i++)
	{
		/* Looping through the delimiter list (string) */
		for (j = 0; j < delimeter_length; j++)
		{
			/* Replacing any delimiter found with (char -> \0) */
			if (str[i] == delimiter[j])
				str[i] = '\0';
		}
	}
	/* Counting the total tokens in the duplicated string */
	while (k < str_len)
	{
		if ((str[k] != '\0' && str[k + 1] == '\0'))
			count++;
		k++;
	}
	return (count);
}

/**
 * str_av - generates a null terminated list of tokens from a string
 * @str: the string argument (note: string is modified)
 * @delimiter: list (string) of delimiters
 *
 * Return: array containig tokens
 */
char **str_av(char *str, char *delimiter)
{
	bool start = false;
	char **av = NULL, *temp_str;
	size_t i = 0, start_pos = 0, stop_pos = 0, curr_pos, ptr = 0, str_len;
	ssize_t count = 0;

	str_len = _strlen(str);
	count = brk_at_delimiter(str, delimiter);
	av = malloc((count + 1) * sizeof(char *));
	exit_on_alloc_fail(av, EXIT_FAILURE);
	for (curr_pos = 0; curr_pos <= str_len; curr_pos++)
	{
		if (start && str[curr_pos] == '\0')
		{
			stop_pos = curr_pos;
			start = false;
			temp_str = malloc((stop_pos - start_pos + 1) * sizeof(char));
			exit_on_alloc_fail(temp_str, EXIT_FAILURE);
			while (start_pos < stop_pos)
			{
				temp_str[ptr] = str[start_pos];
				ptr++, start_pos++;
			}
			temp_str[ptr] = '\0';
			av[i] = temp_str;
			i++;
			ptr = 0;
		}
		if (str[curr_pos] != '\0' && !start)
		{
			start_pos = curr_pos;
			start = true;
		}
	}
	av[count] = NULL;
	return (av);
}
