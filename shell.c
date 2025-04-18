#include "shell.h"

/**
 * execute_command - executes the given command
 * @command: command to execute
 * @program_name: name of the shell program
 * Return: 0 on success, error code on failure
 */
int execute_command(char *command, char *program_name)
{
    pid_t child_pid;
    int status = 0;
    char **args;
    
    if (command == NULL || *command == '\0')
        return 0;
    
    args = tokenize_command(command);
    if (!args || !args[0])
    {
        free_tokens(args);
        return 0;
    }
    
    child_pid = fork();
    
    if (child_pid == -1)
    {
        perror("fork");
        free_tokens(args);
        return 1;
    }
    
    if (child_pid == 0) /* Child process */
    {
        if (execve(args[0], args, environ) == -1)
        {
            fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
            free_tokens(args);
            exit(127);
        }
    }
    else
    {
        waitpid(child_pid, &status, 0);
        free_tokens(args);
        
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
    }
    
    return status;
}

/**
 * tokenize_command - splits a command string into tokens
 * @command: command string to tokenize
 * Return: array of tokens
 */
char **tokenize_command(char *command)
{
    char **tokens = NULL;
    char *token;
    int i = 0;
    char *delim = " \t\r\n\a";
    
    tokens = malloc(sizeof(char *) * 64); /* Can store up to 64 tokens */
    if (!tokens)
    {
        perror("malloc");
        return NULL;
    }
    
    token = strtok(command, delim);
    while (token)
    {
        tokens[i] = strdup(token);
        i++;
        token = strtok(NULL, delim);
    }
    tokens[i] = NULL; /* Null-terminate the array */
    
    return tokens;
}

/**
 * free_tokens - frees the memory allocated for tokens
 * @tokens: array of tokens to free
 */
void free_tokens(char **tokens)
{
    int i;
    
    if (!tokens)
        return;
        
    for (i = 0; tokens[i] != NULL; i++)
        free(tokens[i]);
        
    free(tokens);
}
