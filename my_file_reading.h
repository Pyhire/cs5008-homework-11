#ifndef FILE_READING_H
#define FILE_READING_H

#include <stdio.h>
#include <stdlib.h>

// Define your functions here
void read_cities(char* filename, char*** cities, int* city_count);
void read_distances(char* filename, char** cities, int city_count, int*** distances);

#endif

