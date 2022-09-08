#include "_shell_utils.h"
#include "_strings.h"
#include "_getline.h"

/**
 * generate_command - creates a command list from stdin (av)
 * Return: created command list
 */
char **generate_command()
{
	size_t size = 0;
	ssize_t len;
	char *line = NULL, **av = NULL, *delimiter = " ";
	/* Gets user input from the standard input */
	len = _getline(&line, &size, stdin);
	line[len - 1] = '\0';
	if (len > 1)
	{
		/* Takes the user input and creates an array of each token */
		av = str_av(line, delimiter);
		/* Free the buffer holding the user input */
		free(line);
	}
	return (av);
}

/**
 * free_av - frees the allocted memory to av
 * @av: the command list and its arguments
 */
void free_av(char **av)
{
	size_t i = 0;

	while (av[i] != NULL)
	{
		free(av[i]);
		av[i] = NULL;
		i++;
	}
	free(av[i]);
	av[i] = NULL;
	free(av);
	av = NULL;
}

/**
 * check_command - updates the command as its full path if it exists
 * @av: array of tokens
 */
void check_command(char **av)
{
	ssize_t count;
	char *cmd_cpy1, *cmd, **path_env, *paths_str, *path;
	size_t i = 0, size = 100;
	int mode = F_OK, accessible;

	paths_str = _strdup(getenv("PATH"));
	cmd_cpy1 = _strdup(av[0]);
	cmd = _strdup(av[0]);
	count = brk_at_delimiter(cmd_cpy1, "/");
	if (count == 1)
	{
		path = malloc(size);
		path_env = str_av(paths_str, ":");
		while (path_env[i] != NULL)
		{
			if ((_strlen(path_env[i]) + _strlen(cmd) + 2) > size)
			{
				size = _strlen(path_env[i]) + _strlen(cmd) + 2;
				free(path);
				path = NULL;
				path = malloc(size);
			}
			_strcpy(path, path_env[i]);
			_strcat(path, "/");
			_strcat(path, cmd);
			accessible = access(path, mode);
			if (accessible == 0)
			{
				free(av[0]);
				av[0] = _strdup(path);
			}
			_strcpy(path, "");
			i++;
		}
		free(path);
		free(cmd);
		free(cmd_cpy1);
		free_av(path_env);
		free(paths_str);
	}
}

/**
 * run_shell - runs a command from stdin in the specified shell mode
 * @shell_mode: the shell mode (interactive (true), non interactive (false))
 * @prompt: The text to display as prompt, NULL (uses default prompt)
 * @argv: commandline argument
 * @envp: the shell environment list
 */
void run_shell(bool shell_mode, char *prompt, char **argv, char **envp)
{
	char **av = NULL;
	int exist;

	while (true)
	{
		av = generate_command();
		if (av == NULL && !shell_mode)
			break;
		if (av == NULL)
			continue;
		check_command(av);
		if (_strcmp(av[0], "exit") == 0)
			exit(0);
		exist = access(av[0], F_OK | X_OK);
		if (exist == -1)
		{
			perror(argv[0]);
			free_av(av);
			if (shell_mode)
				continue;
			else
				break;
		}
		exec_cmd(av, envp);
		if (!shell_mode)
			break;
	}
}

/**
 * exec_cmd - exectes a command
 * @av: array of command and its arguments
 * @envp: the list of environment variables
 */
void exec_cmd(char **av, char **envp)
{
	pid_t cpid;

	cpid = fork();
	if (cpid == 0)
	{
		execve(av[0], av, envp);
	}
	else
	{
		wait(NULL);
		free_av(av);
	}
}
