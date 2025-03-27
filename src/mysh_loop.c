#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

char *read_line()
{
    uint16_t LINE_DEFAULT_BUFFERSIZE = 256;
    uint16_t position = 0;
    uint16_t bufferSize = LINE_DEFAULT_BUFFERSIZE;
    char *buffer = (char *)malloc(sizeof(char) * LINE_DEFAULT_BUFFERSIZE);
    if (!buffer)
    {
        printf("Allocation Failed");
        exit(0);
    }
    while (true)
    {
        int currChar = getchar();
        if (currChar == EOF || currChar == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = currChar;
            position++;
        }

        if (position >= bufferSize)
        {
            bufferSize += LINE_DEFAULT_BUFFERSIZE;
            buffer = (char *)realloc(buffer, sizeof(char) * (bufferSize));
            if (!buffer)
            {
                printf("Allocation Failed");
                exit(0);
            }
        }
    }
}

char **get_parameters(char *line)
{
    uint16_t TOKEN_DEFAULT_BUFFERSIZE = 256;
    uint16_t position = 0;
    uint16_t bufferSize = TOKEN_DEFAULT_BUFFERSIZE;
    char **buffer = (char **)malloc(sizeof(char *) * bufferSize);
    if (!buffer){
        printf("Memory allocation failed");
        exit(0);
    }
    char *token = strtok(line, " ");
    while (token != NULL)
    {
        buffer[position] = token;
        token = strtok(NULL, " ");
        position++;

        if(position>=bufferSize){
            bufferSize += TOKEN_DEFAULT_BUFFERSIZE;
            buffer = (char **)realloc(buffer, sizeof(char *) * bufferSize);
            if (!buffer){
                printf("Memory allocation failed");
                exit(0);
            }
        }
    }
    return buffer;
}

void mysh_loop(void)
{
    bool status = true;
    char *line;
    char **args;
    do
    {
        printf("$ ");
        line = read_line();
        args = get_parameters(line);
        for (uint16_t i = 0; args[i] != NULL; i++)
        {
            printf("%s\n", args[i]);
        }
    } while (status);
}