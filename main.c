#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "map.h"

void help()
{
    printf("Commands: \n");
    printf("\tlist - list all cities)\n");
    printf("\t<city1> <city2> - find the shortest path between two cities\n");
    printf("\thelp - print this help message\n");
    printf("\texit - exit the program\n");
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
    if (argc != 3)
    {
        printf("Usage: ./map.out <vertices> <distances>\n");
        exit(0);
    }

    // Create the Graph
    Graph *graph = createGraph();

    // Load cities and distances data from files
    loadCities(graph, argv[1]);
    loadDistances(graph, argv[2]);

    // print the graph for debugging
    // printGraph(graph);

    char city2[50];
    printf("*****Welcome to the shortest path finder!******\n");
    while (1)
    {
        help();
        printf("Where do you want to go today? what do i do? ");

        char command[100];
        scanf("%s", command);

        if (strcmp(command, "list") == 0)
        {
            printf("list\n");
            listCities(graph);
        }
        else if (strcmp(command, "help") == 0)
        {
            continue;
        }
        else if (strcmp(command, "exit") == 0)
        {
            printf("Goodbye!\n");
            break;
        }
        else if (strcmp(command, "print") == 0) // 'hidden command for debugging
        {
            printGraph(graph);
        }
        else
        {
            int src = findCity(graph, command);
            if (src == -1)
            {
                printf("Invalid Command\n");
                continue;
            }
            scanf("%s", city2);
            int dest = findCity(graph, city2);
            if (dest == -1)
            {
                printf("Invalid command\n");
                continue;
            }

            dijkstra(graph, src, dest); // find the shortest path by Dijkstra's algorithm
        }
    }

    return 0;
}