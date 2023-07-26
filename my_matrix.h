#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

// Define your functions here
int** create_graph(int number_of_nodes);
void add_edge(int** graph, int node1, int node2, int weight);
int* dijkstra(int** graph, int city_count, int start_node, int** predecessors);

#endif

