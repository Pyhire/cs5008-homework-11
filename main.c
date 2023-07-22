#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "map.h"

void help()
{
    printf("Commands: \n");
    printf(" list - list all cities)\n");
    printf(" <city1> <city2> - find the shortest path between two cities\n");
    printf(" help - print this help message\n");
    printf(" exit - exit the program\n");
    printf("*******************************************************\n");
}
/**
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[])
{
    char city1[20], city2[20];

    if (argc != 3)
    {
        printf("Usage: ./map.out <vertices> <distances>\n");
        exit(0);
    }

    while (1)
    {
        printf("*****Welcome to the shortest path finder!******\n");
        help();
        printf("Where do you want to go today? what do i do? "); 

        char command[30];
        scanf("%s", command);

        if (strcmp(command, "list") == 0)
        {
            printf("Open command\n");
        }
        else if (strcmp(command, "help") == 0)
        {
            help();
        }
        else if (strcmp(command, "exit") == 0)
        {
            printf("Goodbye!\n");
            break;
        }
        else if (scanf("%s", city2) == 1)
        {
            strcpy(city1, command);
            // scanf("%s", city2);
            printf("city1: %s; city2: %s\n", city1, city2);
        }
        else
        {
            printf("Invalid Command\n");
        }
    }

    return 0;
}