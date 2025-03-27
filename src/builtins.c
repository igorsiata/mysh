#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

int mysh_echo(char **args);
int mysh_exit(char **args);
int mysh_cd(char **args);
int mysh_help(char **args);

char *builtinStr[] = {
    "echo",
    "exit",
    "cd",
    "help"
};

size_t get_number_of_builtin(){
    return sizeof(builtinStr)/sizeof(char *);
}

int (*builtinFunc[])(char **) = {
    &mysh_echo,
    &mysh_exit,
    &mysh_cd,
    &mysh_help
};

int mysh_echo(char **args)
{
    for (size_t i = 1; args[i] != NULL; i++)
    {
        printf("%s ", args[i]);
    }
    printf("\n");
    return 1;
}

int mysh_exit(char **args)
{
    if (args[1] != NULL){
        printf("Error: Wrong arguments\n");
        return 1;
    }
    return 0;
}

int mysh_cd(char **args)
{
    if (args[1] == NULL)
    {
        printf("Error: Wrong arguments\n");
        return 1;
    }
    if(chdir(args[1]) != 0){
        perror("mysh");
    }
    return 1;
}

int mysh_help(char **args)
{
    if(args[1] != NULL)
    {
        printf("Error: Wrong arguments\n");
        return 1;
    }
    size_t numberOfBuiltin = get_number_of_builtin();
    printf("--- MYSH simple shell program ---\n");
    printf("Type command and args separated by space\n");
    printf("- Builtin functions -\n");
    for (size_t i = 0; i < numberOfBuiltin; i++)
    {
        printf("%s\n", builtinStr[i]);
    }
}