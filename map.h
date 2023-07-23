#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Graph
// 1. Adjacent Matrix
// 2. Adjacent List
// 3. Edge List

// Data structure for Vertex
typedef struct Vertex
{
    char *name;
    int id;
    int visited;
    int distance;
    int pre;
} Vertex;

// Data structure for Edge
typedef struct Edge
{
    int src;
    int dest;
    int distance;
} Edge;

// Data structure for Graph
typedef struct Graph
{
    int num_vertices;  // Number of vertices in the graph
    int num_edges;     // Number of edges in the graph
    Vertex **vertices; // Array of vertices
    Edge **edges;      // Array of edges
} Graph;

Graph *createGraph();
void loadCities(Graph *graph, char *filename);
void loadDistances(Graph *graph, char *filename);
void dijkstra(Graph *graph, int src, int dest);
void listCities(Graph *graph);
void addVertex(Graph *graph, char *name);
Vertex *createVertex(int id, char *name);
Edge *createEdge(int src, int dest, int distance);
void addEdge(Graph *graph, int src, int dest, int distance);
int findCity(Graph *graph, char *name);
void printGraph(Graph *graph);

#endif