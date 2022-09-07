#ifndef _GETLINE_H
#define _GETLINE_H
#include <sys/types.h>
#include <stdio.h>
ssize_t _getline(char **lineptr, size_t *size, FILE *stream);
void copy_and_free(char *buff, char **lineptr, size_t *size, size_t newsize);
void update_lineptr(char *buff, char **lineptr);
#endif /* _GETLINE_H */
