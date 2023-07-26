#include <stdio.h>
#include "my_file_reading.h"
#include "my_matrix.h"
#include <limits.h>
#include <string.h>

void print_help() {
    printf("Commands:\n");
    printf("\tlist - list all cities\n");
    printf("\t<city1> <city2> - find the shortest path between two cities\n");
    printf("\thelp - print this help message\n");
    printf("\texit - exit the program\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <cities_file> <distances_file>\n", argv[0]);
        return 1;
    }

    // Load data
    char** cities;
    int city_count;
    read_cities(argv[1], &cities, &city_count);
    int** distances;
    read_distances(argv[2], cities, city_count, &distances);

    print_help();

    // Main loop
    while (1) {
        printf("Where do you want to go today? ");

        // Read input
        char line[256];
        if (!fgets(line, sizeof(line), stdin)) {
            break;
        }

        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        // Handle commands
        if (strcmp(line, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        } else if (strcmp(line, "list") == 0) {
            for (int i = 0; i < city_count; i++) {
                printf("%s\n", cities[i]);
            }
        } else if (strcmp(line, "help") == 0) {
            print_help();
        } else {
            char* city1 = strtok(line, " ");
            char* city2 = strtok(NULL, " ");

            int index1 = -1, index2 = -1;
            for (int i = 0; i < city_count; i++) {
                if (strcmp(city1, cities[i]) == 0) {
                    index1 = i;
                }
                if (strcmp(city2, cities[i]) == 0) {
                    index2 = i;
                }
            }

            if (index1 != -1 && index2 != -1) {
                int* predecessors;
                int* shortest_paths = dijkstra(distances, city_count, index1, &predecessors);
                if (shortest_paths[index2] == INT_MAX) {
                    printf("Path Not Found...\n");
                } else {
                    printf("Path Found...\n");
                    int current_city = index2;
                    int* path = malloc(city_count * sizeof(int));
                    int path_length = 0;
                    while (current_city != -1) {
                        path[path_length++] = current_city;
                        current_city = predecessors[current_city];
                    }
                    for (int i = path_length - 1; i >= 0; i--) {
                        printf("\t%s\n", cities[path[i]]);
                    }
                    printf("Total Distance: %d\n", shortest_paths[index2]);
                    free(path);
                }
                free(shortest_paths);
                free(predecessors);
            } else {
                printf("Invalid Command\n");
                print_help();
            }
        }
    }

    // Clean up
    for (int i = 0; i < city_count; i++) {
        free(cities[i]);
        free(distances[i]);
    }
    free(cities);
    free(distances);

    return 0;
}