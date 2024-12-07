#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char node1[50], node2[50];

    // Open the input file in read mode
    inputFile = fopen("graph_data.txt", "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Open the output CSV file in write mode
    outputFile = fopen("graph_edges.csv", "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);  // Close input file if output fails to open
        return 1;
    }

    // Write the header to the CSV file
    fprintf(outputFile, "Node1, Node2\n");

    // Read each edge from the input file and write it to the CSV file
    while (fscanf(inputFile, "%s %s", node1, node2) == 2) {
        fprintf(outputFile, "%s, %s\n", node1, node2);
    }

    // Close both files
    fclose(inputFile);
    fclose(outputFile);

    printf("Data successfully written to graph_edges.csv\n");
    return 0;
}
