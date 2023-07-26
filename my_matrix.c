#include "my_matrix.h"
#include <limits.h>

// int **create_graph(int city_count)
// {
//     // Allocate memory for the adjacency matrix
//     int **graph = malloc(city_count * sizeof(int *));
//     for (int i = 0; i < city_count; i++)
//     {
//         graph[i] = malloc(city_count * sizeof(int));
//         for (int j = 0; j < city_count; j++)
//         {
//             // Initialize all distances to infinity
//             graph[i][j] = INT_MAX;
//         }
//     }
//     return graph;
// }

// void add_edge(int **graph, int city1, int city2, int distance)
// {
//     // Add the edge in both directions (since this is an undirected graph)
//     graph[city1][city2] = distance;
//     graph[city2][city1] = distance;
// }

int *dijkstra(int **graph, int city_count, int start_node, int **predecessors)
{
    // Initialize shortest paths array
    int *shortest_paths = malloc(city_count * sizeof(int));
    *predecessors = malloc(city_count * sizeof(int));
    for (int i = 0; i < city_count; i++)
    {
        shortest_paths[i] = INT_MAX;
        (*predecessors)[i] = -1; // -1 indicates no predecessor
    }
    shortest_paths[start_node] = 0;

    // Initialize visited array
    int *visited = calloc(city_count, sizeof(int));

    for (int count = 0; count < city_count - 1; count++)
    {
        // Find minimum distance node that has not been visited
        int min = INT_MAX, min_index;
        for (int v = 0; v < city_count; v++)
        {
            if (visited[v] == 0 && shortest_paths[v] <= min)
                min = shortest_paths[v], min_index = v;
        }

        // Mark the picked vertex as processed
        visited[min_index] = 1;

        // Update shortest_paths value and predecessor of the adjacent vertices of the picked vertex
        for (int v = 0; v < city_count; v++)
        {
            if (!visited[v] && graph[min_index][v] < INT_MAX && shortest_paths[min_index] != INT_MAX && shortest_paths[min_index] + graph[min_index][v] < shortest_paths[v])
            {
                shortest_paths[v] = shortest_paths[min_index] + graph[min_index][v];
                (*predecessors)[v] = min_index;
            }
        }
    }

    free(visited);
    return shortest_paths;
}
