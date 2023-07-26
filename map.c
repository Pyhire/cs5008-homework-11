#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "map.h"

Graph *createGraph()
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->num_edges = 0;
    graph->num_vertices = 0;
    graph->vertices = (Vertex **)malloc(sizeof(Vertex *));
    graph->edges = (Edge **)malloc(sizeof(Edge *));

    return graph;
}

void loadVertices(Graph *graph, char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[100];
    char name[100];
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%s", name);
        // TODO: handle duplicate vertex
        addVertex(graph, name);
    }

    fclose(file); // close file
}

void loadEdges(Graph *graph, char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("\nError: Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[100];
    char city1[50], city2[50];
    int distance;

    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%s %s %d", city1, city2, &distance);

        int src = findCity(graph, city1);
        int dest = findCity(graph, city2);
        if (src == -1 || dest == -1)
        {
            printf("\nError: Citys in distance files are not in City file: (%s %s %d)\n", city1, city2, distance);
            exit(EXIT_FAILURE);
        }

        // TODO: handle duplicate edge
        addEdge(graph, src, dest, distance);
    }

    fclose(file);
}

int minDistance(Vertex *vertex)
{
    return 0;
}

void dijkstra(Graph *graph, int src, int dest)
{
    // Initialize all vertices' distance to INFINITY and visited flag to 0
    for (int i = 0; i < graph->num_vertices; i++)
    {
        graph->vertices[i]->distance = INT_MAX;
        graph->vertices[i]->visited = 0;
        graph->vertices[i]->prev = -1;
    }

    // Set the distance for the source to 0
    graph->vertices[src]->distance = 0;

    for (int i = 0; i < graph->num_vertices - 1; i++)
    {
        // Find the minimum distance vertex from the set of vertices not yet processed
        int min = INT_MAX, min_index;
        for (int v = 0; v < graph->num_vertices; v++)
        {
            if (graph->vertices[v]->visited == 0 && graph->vertices[v]->distance <= min)
            {
                min = graph->vertices[v]->distance;
                min_index = v;
            }
        }

        // Mark the picked vertex as processed
        graph->vertices[min_index]->visited = 1;

        // Update distance value of the adjacent vertices of the picked vertex
        for (int e = 0; e < graph->num_edges; e++)
        {
            if (graph->edges[e]->src == min_index && graph->vertices[graph->edges[e]->dest]->visited == 0)
            {
                int newDist = graph->vertices[min_index]->distance + graph->edges[e]->distance;
                if (newDist < graph->vertices[graph->edges[e]->dest]->distance)
                {
                    graph->vertices[graph->edges[e]->dest]->distance = newDist;
                    graph->vertices[graph->edges[e]->dest]->prev = min_index;
                }
            }
        }
    }

    printf("Path Found...\n");

    // Print the shortest path from src to dest
    printPath(graph, src, dest);

    printf("\nTotal Distance: %d\n", 100); // TODO
}

void printPath(Graph *graph, int src, int dest)
{
    if (dest == src)
    {
        printf("%s\n", graph->vertices[src]->name);
        return;
    }

    printPath(graph, src, graph->vertices[dest]->prev);

    printf("%s \n", graph->vertices[dest]->name);
}

Vertex *createVertex(int id, char *name)
{
    // printf("name is %s\n", name);
    Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));
    vertex->id = id;
    vertex->name = (char *)malloc(strlen(name));
    strcpy(vertex->name, name);

    return vertex;
}

Edge *createEdge(int src, int dest, int distance)
{
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    edge->src = src;
    edge->dest = dest;
    edge->distance = distance;

    return edge;
}

void addVertex(Graph *graph, char *name)
{
    int id = graph->num_vertices;
    graph->vertices = (Vertex **)realloc(graph->vertices, ++graph->num_vertices * sizeof(Vertex *));
    // printf("the current vertex's name is: %s id is: %d\n", name, id);
    graph->vertices[id] = createVertex(id, name);
}

void addEdge(Graph *graph, int src, int dest, int distance)
{
    int id = graph->num_edges;
    graph->edges = (Edge **)realloc(graph->edges, ++graph->num_edges * sizeof(Edge *));
    graph->edges[id] = createEdge(src, dest, distance);
}

int findCity(Graph *graph, char *name)
{
    for (int i = 0; i < graph->num_vertices; i++)
    {
        if (strcmp(graph->vertices[i]->name, name) == 0)
        {
            return graph->vertices[i]->id;
        }
    }
    // not found the city
    return -1;
}

void listCity(Graph *graph)
{
    for (int i = 0; i < graph->num_vertices; i++)
    {
        printf("%s\n", graph->vertices[i]->name);
    }
}

void printGraph(Graph *graph)
{
    printf("Vertices:\n");
    for (int i = 0; i < graph->num_vertices; i++)
    {
        Vertex *vertex = graph->vertices[i];
        printf("Vertex(%d, %s)\n", vertex->id, vertex->name);
    }

    printf("Edges:\n");
    for (int i = 0; i < graph->num_edges; i++)
    {
        Edge *edge = graph->edges[i];
        printf("Edge(%d, %d, %d)\n", edge->src, edge->dest, edge->distance);
    }
}

void freeGraph(Graph *graph)
{
    for (int i = 0; i < graph->num_vertices; i++)
    {
        free(graph->vertices[i]);
    }

    for (int i = 0; i < graph->num_edges; i++)
    {
        free(graph->edges[i]);
    }
}
