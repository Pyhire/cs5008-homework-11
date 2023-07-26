#include "my_file_reading.h"
#include <limits.h>
#include <string.h>

void read_cities(char* filename, char*** cities, int* city_count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot open file %s\n", filename);
        return;
    }

    // Initialize variables
    *city_count = 0;
    *cities = NULL;

    // Read lines from file
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        // Increase city count and resize cities array
        (*city_count)++;
        *cities = realloc(*cities, *city_count * sizeof(char*));

        // Copy city name
        (*cities)[*city_count - 1] = strdup(line);
    }

    fclose(file);
}

void read_distances(char* filename, char** cities, int city_count, int*** distances) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot open file %s\n", filename);
        return;
    }

    // Initialize distance matrix
    *distances = malloc(city_count * sizeof(int*));
    for (int i = 0; i < city_count; i++) {
        (*distances)[i] = malloc(city_count * sizeof(int));
        for (int j = 0; j < city_count; j++) {
            (*distances)[i][j] = INT_MAX;
        }
    }

    // Read lines from file
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Parse line
        char* city1 = strtok(line, " ");
        char* city2 = strtok(NULL, " ");
        int distance = atoi(strtok(NULL, " "));

        // Find city indices
        int index1 = -1, index2 = -1;
        for (int i = 0; i < city_count; i++) {
            if (strcmp(city1, cities[i]) == 0) {
                index1 = i;
            }
            if (strcmp(city2, cities[i]) == 0) {
                index2 = i;
            }
        }

        // Update distance matrix
        if (index1 != -1 && index2 != -1) {
            (*distances)[index1][index2] = distance;
            (*distances)[index2][index1] = distance;
        }
    }

    fclose(file);
}
