#include "shell.h"

/**
 * main - entry point for simple shell
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int status = 0;
    (void)argc;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("#cisfun$ ");

        read = getline(&line, &len, stdin);
        
        if (read == -1)
        {
            if (isatty(STDIN_FILENO))
                printf("\n");
            break;
        }

        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        status = execute_command(line, argv[0]);
    }

    if (line)
        free(line);
    
    return status;
}
