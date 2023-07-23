#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "map.h"

Graph *createGraph()
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (graph == NULL)
    {
        printf("Memory allocation Failed\n");
        exit(EXIT_FAILURE);
    }

    graph->num_vertices = 0;
    graph->num_edges = 0;
    graph->vertices = (Vertex **)malloc(sizeof(Vertex *));
    graph->edges = (Edge **)malloc(sizeof(Edge *));

    return graph;
}

void loadCities(Graph *graph, char *filename)
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

        addVertex(graph, name);
    }

    fclose(file);
}

void loadDistances(Graph *graph, char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[100];
    char city1[30], city2[30];
    int distance;
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%s %s %d", city1, city2, &distance);
        int src = findCity(graph, city1);
        int dest = findCity(graph, city2);
        if (src == -1 || dest == -1)
        {
            printf("Error: Could not find city %s or %s\n", city1, city2);
            exit(EXIT_FAILURE);
        }

        addEdge(graph, src, dest, distance);
    }

    fclose(file);
}

void dijkstra(Graph *graph, int src, int dest)
{
}

void listCities(Graph *graph)
{
    for (int i = 0; i < graph->num_vertices; i++)
    {
        printf("%s\n", graph->vertices[i]->name);
    }
}

void addVertex(Graph *graph, char *name)
{
    int id = graph->num_vertices;
    graph->vertices = (Vertex **)realloc(graph->vertices, ++graph->num_vertices * sizeof(Vertex *));

    graph->vertices[id] = createVertex(id, name);
}

Vertex *createVertex(int id, char *name)
{
    Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));
    if (vertex == NULL)
    {
        printf("Error: Could not allocate memory for vertex\n");
        exit(EXIT_FAILURE);
    }

    vertex->id = id;
    vertex->name = (char *)malloc(strlen(name) + 1);
    strcpy(vertex->name, name);

    return vertex;
}

Edge *createEdge(int src, int dest, int distance)
{
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    if (edge == NULL)
    {
        printf("Error: Could not allocate memory for edge\n");
        exit(EXIT_FAILURE);
    }

    edge->src = src;
    edge->dest = dest;
    edge->distance = distance;

    return edge;
}

void addEdge(Graph *graph, int src, int dest, int distance)
{
    int id = graph->num_edges;
    graph->edges = (Edge **)realloc(graph->edges, ++graph->num_edges * sizeof(Edge *));

    graph->edges[id] = createEdge(src, dest, distance);
}

int findCity(Graph *graph, char *name)
{
    for (int i = 0; i < graph->num_vertices; ++i)
    {
        if (strcmp(graph->vertices[i]->name, name) == 0)
        {
            return graph->vertices[i]->id;
        }
    }

    // not found the city
    return -1;
}

void printGraph(Graph *graph)
{
    printf("Cities:\n");
    for (int i = 0; i < graph->num_vertices; i++)
    {
        Vertex *vertex = graph->vertices[i];
        printf("Vertex(%d, %s)\n", vertex->id, vertex->name);
    }

    printf("\nEdges:\n");
    for (int i = 0; i < graph->num_edges; i++)
    {
        Edge *edge = graph->edges[i];
        printf("Edge(%d, %d, %d)\n", edge->src, edge->dest, edge->distance);
    }
}
