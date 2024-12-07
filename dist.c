#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_DISTRICTS 65
#define MAX_DISTANCE 700
#define MIN_DISTANCE 25
#define INF 99999
#define FILENAME "graph_data.txt"

// Function to generate random distances
int generateDistance() {
    // 20% chance of no connection
    if (rand() % 100 < 30) {
        return INF;
    }
    // Random distance between MIN_DISTANCE and MAX_DISTANCE
    return MIN_DISTANCE + rand() % (MAX_DISTANCE - MIN_DISTANCE + 1);
}

int main() {
    int matrix[NUM_DISTRICTS][NUM_DISTRICTS];
    FILE *file;

    // Seed the random number generator
    srand(time(NULL));

    // Generate the adjacency matrix
    for (int i = 0; i < NUM_DISTRICTS; i++) {
        for (int j = 0; j < NUM_DISTRICTS; j++) {
            if (i == j) {
                matrix[i][j] = 0; // Distance to self is 0
            } else if (j > i) {
                matrix[i][j] = generateDistance(); // Random distance or INF
            } else {
                matrix[i][j] = matrix[j][i]; // Ensure symmetry
            }
        }
    }

    // Save the matrix to a text file
    file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error: Could not open file '%s' for writing.\n", FILENAME);
        return 1;
    }

    for (int i = 0; i < NUM_DISTRICTS; i++) {
        for (int j = 0; j < NUM_DISTRICTS; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);

    printf("Simulated 65x65 adjacency matrix saved to '%s'.\n", FILENAME);

    return 0;
}
