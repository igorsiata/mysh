#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "builtins.c"

int mysh_launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();

    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("mysh");
        }
    }
    else if (pid < 0)
    {
        perror("mysh");
    }
    else if (pid > 0)
    {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int mysh_execute(char **args)
{
    if (args[0] == NULL)
    {
        printf("Error: No command specified\n");
        return 1;
    }
    size_t numberOfBuiltin = get_number_of_builtin();
    for (size_t i = 0; i < numberOfBuiltin; i++)
    {
        if (strcmp(args[0], builtinStr[i]) == 0)
        {
            return (*builtinFunc[i])(args);
        }
    }
    return mysh_launch(args);
}