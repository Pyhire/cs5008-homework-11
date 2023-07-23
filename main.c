#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "map.h"

void help()
{
    printf("*****Welcome to the shortest path finder!******\n");
    printf("Commands: \n");
    printf(" list - list all cities)\n");
    printf(" <city1> <city2> - find the shortest path between two cities\n");
    printf(" help - print this help message\n");
    printf(" exit - exit the program\n");
    printf("*******************************************************\n");
}

/**
 * The entrance of the program
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[])
{
    char city2[50];

    if (argc != 3)
    {
        printf("Usage: ./map.out <vertices> <distances>\n");
        exit(0);
    }

    // create the graph
    Graph *graph = createGraph();

    // load data from files to initialize the graph
    loadVertices(graph, argv[1]);
    loadEdges(graph, argv[2]);

    // print the graph, just for debugging
    printGraph(graph);

    while (1)
    {
        help();
        printf("Where do you want to go today? what do i do? ");

        char command[100];
        scanf("%s", command);

        if (strcmp(command, "list") == 0)
        {
            listCity(graph);
            printf("\n");
        }
        else if (strcmp(command, "help") == 0)
        {
            continue;
        }
        else if (strcmp(command, "exit") == 0)
        {
            printf("Goodbye!\n");
            freeGraph(graph);
            exit(0);
        }
        else
        {
            int src = findCity(graph, command);
            if (src == -1)
            {
                printf("Invalid Command\n");
            }
            else
            {
                scanf("%s", city2);
                int dest = findCity(graph, city2);

                if (dest == -1)
                {
                    printf("Invalid Command\n");
                }
                else
                {
                    dijkstra(graph, src, dest);
                }
            }
        }
    }

    freeGraph(graph);

    return 0;
}