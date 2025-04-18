#include "shell.h"

/**
 * builtin_exit - handles the exit built-in
 * @args: arguments to exit
 * Return: exit status
 */
int builtin_exit(char **args)
{
    int status = 0;
    
    free_tokens(args);
    
    exit(status);
}

/**
 * builtin_env - handles the env built-in
 * Return: 0 on success
 */
int builtin_env(void)
{
    int i;
    
    for (i = 0; environ[i]; i++)
        printf("%s\n", environ[i]);
        
    return 0;
}
