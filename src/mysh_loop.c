#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "command_execution.c"
#include "input_processing.c"

void mysh_loop(void)
{
    int status;
    char *line;
    char **args;
    do
    {
        printf("$ ");
        line = read_line();
        args = get_parameters(line);
        status = mysh_execute(args);

        free(line);
        free(args);
    } while (status);
}