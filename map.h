#ifndef MAP_H
#define MAP_H

// Structure to represent a vertex in the graph.
typedef struct Vertex
{
    char *name;   // Name of the vertex.
    int id;       // Unique identifier for the vertex.
    int distance; // Distance from the source vertex.
    int visited;  // Flag to indicate if the vertex has been visited.
    int prev;     // ID of the previous vertex in the path.
} Vertex;

// Structure to represent an edge in the graph.
typedef struct Edge
{
    int src;      // ID of the source vertex.
    int dest;     // ID of the destination vertex.
    int distance; // distance of the edge.
} Edge;

// Graph data structure.
typedef struct Graph
{
    int num_vertices;  // Number of vertices in the graph.
    int num_edges;     // Number of edges in the graph.
    Vertex **vertices; // Array of vertices in the graph.
    Edge **edges;      // Array of edges in the graph.
} Graph;

Graph *createGraph();
void loadVertices(Graph *graph, char *filename);
void loadEdges(Graph *graph, char *filename);
int minDistance(Vertex *vertex);
void dijkstra(Graph *graph, int src, int dest);
Vertex *createVertex(int id, char *name);
Edge *createEdge(int src, int dest, int distance);
void addVertex(Graph *graph, char *name);
void addEdge(Graph *graph, int src, int dest, int distance);
int findCity(Graph *graph, char *name);
void listCity(Graph *graph);
void printPath(Graph *graph, int src, int dest);
void printGraph(Graph *graph);
void freeGraph(Graph *graph);

#endif