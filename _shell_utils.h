#ifndef _SHELL_UTILS_H
#define _SHELL_UTILS_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
void print(char *str, int fd);
void print_prompt(char *str, bool shell_mode);
bool shell_mode(int fd);
int _fileno(FILE *stream);
ssize_t brk_at_delimiter(char *str, char *delimiter);
char **str_av(char *str, char *delimiter);
char **generate_command();
void free_av(char **av);
void run_shell(bool mode, char *prompt, char **argv, char **envp);
void exit_on_alloc_fail(void *block, int status);
void check_command(char **av);
void exec_cmd(char **av, char **envp);
#endif /* _SHELL_UTILS_H */
