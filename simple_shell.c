#include "_shell_utils.h"
#include "_strings.h"
#include "_getline.h"

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument list
 * @envp: environment variables list
 *
 * Return: 0 on Success, non-zero integer otherwise
 */

int main(int argc, char **argv, char **envp)
{
	char *CLEAR_SCREEN_ANSI;

	/* Execute the file without any argument */
	if (argc != 1)
	{
		print("Usage: simple_shell\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	CLEAR_SCREEN_ANSI = "\033[1;1H\033[2J";

	print(CLEAR_SCREEN_ANSI, STDOUT_FILENO);
	while (true)
	{
		/* shell currnet mode (interactive (true), non interactive(false)) */
		bool shell_current_mode = shell_mode(STDIN_FILENO);
		/* Run shell in the specified shellmode */
		run_shell(shell_current_mode, NULL, argv, envp);
		return (0);
	}
}
