#include <string.h>
#include <limits.h>
#include "my_matrix.h"
#include "my_file_reading.h"

int unitTest_01()
{
  int passed = 0;

  char **cities;
  int city_count;
  char filename[] = "vertices.txt";
  read_cities(filename, &cities, &city_count);

  int expected = 8;
  int actual = city_count;
  if (expected == actual)
  {
    passed = 1;
  }

  if (strcmp(cities[5], "f") != 0)
  {
    passed = 0;
  }

  return passed;
}

int unitTest_02()
{
  int passed = 0;

  char **cities;
  int city_count;
  char filename[] = "distances.txt";
  int **distances;
  char vfilename[] = "vertices.txt";
  read_cities(vfilename, &cities, &city_count); // read_distances rely on read_cities
  read_distances(filename, cities, city_count, &distances);

  int expected = 8;
  int actual = distances[5][2];
  if (expected == actual)
  {
    passed = 1;
  }

  return passed;
}

int unitTest_03()
{
  int passed = 0;

  char **cities;
  int city_count;
  char filename[] = "distances.txt";
  int **distances;
  char vfilename[] = "vertices.txt";
  read_cities(vfilename, &cities, &city_count); // read_distances rely on read_cities
  read_distances(filename, cities, city_count, &distances);

  int src = 0;  // "a" vertex
  int dest = 5; // "f" vertex
  int *predecessors;
  int *shortest_paths = dijkstra(distances, city_count, src, &predecessors);

  int expected = 10;
  int actual = shortest_paths[dest]; // Path Found Case
  if (expected == actual)
  {
    passed = 1;
  }

  return passed;
}

int unitTest_04()
{
  int passed = 0;

  char **cities;
  int city_count;
  char filename[] = "distances.txt";
  int **distances;
  char vfilename[] = "vertices.txt";
  read_cities(vfilename, &cities, &city_count); // read_distances rely on read_cities
  read_distances(filename, cities, city_count, &distances);

  int src = 0;  // "a" vertex
  int dest = 7; // "x" vertex
  int *predecessors;
  int *shortest_paths = dijkstra(distances, city_count, src, &predecessors);

  int expected = INT_MAX;
  int actual = shortest_paths[dest]; // Path Found Case
  if (expected == actual)
  {
    passed = 1;
  }

  return passed;
}

// An array of function pointers to all of the tests
// that main() can use iterate over them.
// UNCOMMENT Tests as you are ready to use them
// Add your own tests!
int (*unitTests[])(int) = {
    unitTest_01,
    unitTest_02,
    unitTest_03,
    unitTest_04,
    NULL};

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main()
{
  unsigned int testsPassed = 0;
  // List of Unit Tests to test your data structure
  int counter = 0;
  while (unitTests[counter] != NULL)
  {
    printf("========unitTest %d========\n", counter);
    if (1 == unitTests[counter](1))
    {
      printf("passed test\n");
      testsPassed++;
    }
    else
    {
      printf("failed test, missing functionality, or incorrect test\n");
    }
    counter++;
  }

  printf("%d of %d tests passed\n", testsPassed, counter);

  return 0;
}