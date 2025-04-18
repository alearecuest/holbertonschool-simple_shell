#include "shell.h"

/**
 * find_command_path - finds the full path of a command
 * @command: command to find
 * Return: full path of command if found, NULL if not
 */
char *find_command_path(char *command)
{
    char *path_env, *path_copy, *path_token, *file_path;
    int command_len, dir_len;
    struct stat buffer;
    
    if (!command)
        return NULL;
    
    if (strchr(command, '/') != NULL)
    {
        if (stat(command, &buffer) == 0 && (buffer.st_mode & S_IXUSR))
            return strdup(command);
        return NULL;
    }
    
    path_env = getenv("PATH");
    if (!path_env)
        return NULL;
    
    path_copy = strdup(path_env);
    if (!path_copy)
        return NULL;
    
    command_len = strlen(command);
    
    path_token = strtok(path_copy, ":");
    while (path_token)
    {
        dir_len = strlen(path_token);
        
        file_path = malloc(dir_len + command_len + 2);
        if (!file_path)
        {
            free(path_copy);
            return NULL;
        }
        
        strcpy(file_path, path_token);
        strcat(file_path, "/");
        strcat(file_path, command);
        
        if (stat(file_path, &buffer) == 0 && (buffer.st_mode & S_IXUSR))
        {
            free(path_copy);
            return file_path;
        }
        
        free(file_path);
        path_token = strtok(NULL, ":");
    }
    
    free(path_copy);
    return NULL;
}
