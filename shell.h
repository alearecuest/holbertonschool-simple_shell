#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

int execute_command(char *command, char *program_name);
char **tokenize_command(char *command);
void free_tokens(char **tokens);
char *find_command_path(char *command);
int builtin_exit(char **args);
int builtin_env(void);

extern char **environ;

#endif /* SHELL_H */
