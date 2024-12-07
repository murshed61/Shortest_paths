#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<stdlib.h>
#include<time.h>

#define NUM_DISTRICTS 65
#define FILENAME "graph_data.txt"
#define INF 9999999
typedef struct division
{
    const char *division;
    const char *districts[20];
} Division;

const Division divisions[] =
{
    {"Barishal", {"Barguna", "Barishal", "Bhola", "Jhalokati", "Patuakhali", "Pirojpur"}},
    {
        "Chattogram", {"Bandarban", "Brahmanbaria", "Chandpur", "Chattogram", "Cox's Bazar",
            "Cumilla", "Feni", "Khagrachari", "Lakshmipur", "Noakhali", "Rangamati"
        }
    },
    {
        "Dhaka", {"DSC","Dhaka", "Faridpur", "Gazipur", "Gopalganj", "Kishoreganj",
            "Madaripur", "Manikganj", "Munshiganj", "Narayanganj", "Narsingdi",
            "Rajbari", "Shariatpur", "Tangail"
        }
    },
    {
        "Khulna", {"Bagerhat", "Chuadanga", "Jashore", "Jhenaidah", "Khulna",
            "Kushtia", "Magura", "Meherpur", "Narail", "Satkhira"
        }
    },
    {"Mymensingh", {"Jamalpur", "Mymensingh", "Netrokona", "Sherpur"}},
    {
        "Rajshahi", {"Bogra", "Chapai Nawabganj","Joypurhat", "Naogaon", "Natore", "Pabna",
            "Rajshahi", "Sirajganj"
        }
    },
    {
        "Rangpur", {"Dinajpur", "Gaibandha", "Kurigram", "Lalmonirhat", "Nilphamari",
            "Panchagarh", "Rangpur", "Thakurgaon"
        }
    },
    {"Sylhet", {"Habiganj", "Moulvibazar", "Sunamganj", "Sylhet"}}
};
// District names
const char *districts[] =
{
    "DSC", "Bagerhat", "Bandarban", "Barguna", "Barishal", "Bhola", "Bogra",
    "Brahmanbaria", "Chandpur","Chapai Nawabganj", "Chattogram", "Chuadanga", "Cox's Bazar",
    "Cumilla", "Dhaka", "Dinajpur", "Faridpur", "Feni", "Gaibandha", "Gazipur",
    "Gopalganj", "Habiganj", "Jamalpur", "Jashore", "Jhalokati", "Jhenaidah",
    "Joypurhat", "Khagrachari", "Khulna", "Kishoreganj", "Kurigram", "Kushtia",
    "Lakshmipur", "Lalmonirhat", "Madaripur", "Magura", "Manikganj", "Meherpur",
    "Moulvibazar", "Munshiganj", "Mymensingh", "Naogaon", "Narail", "Narayanganj",
    "Narsingdi", "Natore", "Netrokona", "Nilphamari", "Noakhali", "Pabna",
    "Panchagarh", "Patuakhali", "Pirojpur", "Rajbari", "Rajshahi", "Rangamati",
    "Rangpur", "Satkhira", "Shariatpur", "Sherpur", "Sirajganj", "Sunamganj",
    "Sylhet", "Tangail", "Thakurgaon"
};
char district2[64][50]=
{
    "Barguna", "Barishal", "Bhola", "Jhalokati", "Patuakhali", "Pirojpur","Bandarban", "Brahmanbaria", "Chandpur", "Chattogram", "Cox's Bazar",
    "Cumilla", "Feni", "Khagrachari", "Lakshmipur", "Noakhali", "Rangamati","Dhaka", "Faridpur", "Gazipur", "Gopalganj", "Kishoreganj",
    "Madaripur", "Manikganj", "Munshiganj", "Narayanganj", "Narsingdi",
    "Rajbari", "Shariatpur", "Tangail","Bagerhat", "Chuadanga", "Jashore", "Jhenaidah", "Khulna",
    "Kushtia", "Magura", "Meherpur", "Narail", "Satkhira","Jamalpur", "Mymensingh", "Netrokona", "Sherpur","Bogra", "Chapai Nawabganj","Joypurhat", "Naogaon", "Natore", "Pabna",
    "Rajshahi", "Sirajganj","Dinajpur", "Gaibandha", "Kurigram", "Lalmonirhat", "Nilphamari",
    "Panchagarh", "Rangpur", "Thakurgaon","Habiganj", "Moulvibazar", "Sunamganj", "Sylhet"
};
// Function Declartions//
void readGraph(int graph[NUM_DISTRICTS][NUM_DISTRICTS]);
void displayGraph(int graph[NUM_DISTRICTS][NUM_DISTRICTS]);
void display_menu();
void distance_from_dsc(int graph[NUM_DISTRICTS][NUM_DISTRICTS]);
void bellmanFord(int graph[NUM_DISTRICTS][NUM_DISTRICTS], int src, int dest);
void nearestNeighbors(int graph[NUM_DISTRICTS][NUM_DISTRICTS], int src, int dest);
void printPath(int parent[], int dest);
void print_all();
void clear();
////////////////////////////

void readGraph(int graph[NUM_DISTRICTS][NUM_DISTRICTS])
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file '%s' for reading.\n", FILENAME);
    }

    for (int i = 0; i < NUM_DISTRICTS; i++)
    {
        for (int j = 0; j < NUM_DISTRICTS; j++)
        {
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    fclose(file);
    printf("Graph successfully loaded from '%s'.\n", FILENAME);
}
void displayGraph(int graph[NUM_DISTRICTS][NUM_DISTRICTS])
{
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < NUM_DISTRICTS; i++)
    {
        for (int j = 0; j < NUM_DISTRICTS; j++)
        {
            if (graph[i][j] == 99999)
                printf("No.%d Distance From %s TO %s is : %s\n",i+1, districts[i], districts[j], "INF");
            else
                printf("No.%d Distance From %s TO %s is: %d Kilometer\n",i+1, districts[i], districts[j], graph[i][j]);
        }
        printf("\n");
    }
}
int findNearestNeighbor(int graph[NUM_DISTRICTS][NUM_DISTRICTS], int current, int visited[])
{
    int minDist = INF;
    int nearest = -1;

    for (int i = 0; i < NUM_DISTRICTS; i++)
    {
        if (!visited[i] && graph[current][i] < minDist)
        {
            minDist = graph[current][i];
            nearest = i;
        }
    }
    return nearest;
}
void nearestNeighbors(int graph[NUM_DISTRICTS][NUM_DISTRICTS], int src, int dest)
{
    int visited[NUM_DISTRICTS] = {0}; // Track visited nodes
    int current = src;               // Start from the source
    int path[NUM_DISTRICTS];         // To store the path
    int pathIndex = 0;               // Path index
    int totalDistance = 0;

    visited[current] = 1;            // Mark source as visited
    path[pathIndex++] = current;     // Add source to path

    while (current != dest)
    {
        int nearest = findNearestNeighbor(graph, current, visited);
        if (nearest == -1 || graph[current][nearest] == INF)
        {
            printf("No path exists from %d to %d.\n", src, dest);
            return;
        }

        totalDistance += graph[current][nearest];
        current = nearest;
        visited[current] = 1;
        path[pathIndex++] = current;
    }


    printf("\n**************************************************\n");
    printf(" Total Distance from Node %s to Node %s: %d\n", districts[src], districts[dest], totalDistance);
    printf("**************************************************\n");
    printf("\nPath taken: ");

    for (int i = 0; i < pathIndex; i++)
    {
        printf("%s->", districts[path[i]]);
    }
    printf("\n---------------------------------------------\n");
}
int findMinDistance(int dist[], int visited[])
{
    int min = INF, minIndex = -1;

    for (int v = 0; v < NUM_DISTRICTS; v++)
    {
        if (!visited[v] && dist[v] < min)
        {
            min = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}
void bellmanFord(int graph[NUM_DISTRICTS][NUM_DISTRICTS], int src, int dest)
{
    int dist[NUM_DISTRICTS];
    int parent[NUM_DISTRICTS];


    for (int i = 0; i < NUM_DISTRICTS; i++)
    {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[src] = 0; // Distance to the source is 0

    // Relax all edges |V|-1 times
    for (int i = 1; i < NUM_DISTRICTS; i++)
    {
        for (int u = 0; u < NUM_DISTRICTS; u++)
        {
            for (int v = 0; v < NUM_DISTRICTS; v++)
            {
                if (graph[u][v] != INF && dist[u] + graph[u][v] < dist[v])
                {
                    dist[v] = dist[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u < NUM_DISTRICTS; u++)
    {
        for (int v = 0; v < NUM_DISTRICTS; v++)
        {
            if (graph[u][v] != INF && dist[u] + graph[u][v] < dist[v])
            {
                printf("Graph contains a negative-weight cycle!\n");
                return;
            }
        }
    }

    // Print the result
    if (dist[dest] == INF)
    {
        printf("No path exists from %d to %d.\n", src, dest);
    }
    else
    {
        printf("\n-------------------------------------------\n");
        printf("Shortest distance from %s to %s: %d\n", districts[src],districts[dest], dist[dest]);
        printf("-------------------------------------------\n");
        printf("Path Taken:");
        printPath(parent, dest);
        printf("\n-------------------------------------------\n");
    }
}
void dijkstra(int graph[NUM_DISTRICTS][NUM_DISTRICTS], int src, int dest)
{
    int dist[NUM_DISTRICTS];          // Array to hold shortest distances
    int visited[NUM_DISTRICTS] = {0}; // Track visited vertices
    int parent[NUM_DISTRICTS];        // To store the shortest path tree

    // Initialize distances to INF and parent to -1
    for (int i = 0; i < NUM_DISTRICTS; i++)
    {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int count = 0; count < NUM_DISTRICTS - 1; count++)
    {
        int u = findMinDistance(dist, visited);
        visited[u] = 1;

        for (int v = 0; v < NUM_DISTRICTS; v++)
        {
            if (!visited[v] && graph[u][v] != INF && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Beautifully formatted shortest distance output
    printf("\n***********************************************\n");
    printf(" Total Distance from Node %s to %s: %d\n", districts[src], districts[dest], dist[dest]);
    printf("***********************************************\n");
    printf("Path taken: ");
    printPath(parent, dest);

    printf("\n-------------------------------------------\n");
    printf("Press Enter To continue......\n");
    getchar();
}
void printPath(int parent[], int dest)
{
    if (parent[dest] == -1)
    {
        printf("%s", districts[dest]);
        return;
    }
    printPath(parent, parent[dest]);
    printf("->%s", districts[dest]);
}

int main()
{
    while(1)
    {
        int graph[NUM_DISTRICTS][NUM_DISTRICTS];
        readGraph(graph);
        system("cls");
        //displayGraph(graph);
        display_menu();
        int choice;
        printf("->>");
        scanf(" %d", &choice);
        switch (choice)
        {
        case 1:
            distance_from_dsc(graph);
            break;
        case 2:
            print_all();
            break;
        default:
            printf("Enter a valid input\n");
            break;
        }
        clear();
        getchar();
    }


    return 0;
}
void toUpperString(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper(str[i]);
    }
}
void distance_from_dsc(int graph[NUM_DISTRICTS][NUM_DISTRICTS])
{
    system("cls");
    srand(time(NULL));
    printf("=======================================\n");
    printf("           FIND DISTANCE TOOL          \n");
    printf("=======================================\n");
    printf("      // Find Distance From DSC//\n\n");
    printf("Suggested/Sample: ");
    for(int i = 0; i<5; i++)
    {
        int index = rand()%64;
        printf("[%s] ",district2[index]);
    }
    printf("\n\nEnter the name of the district: ");
    char zilla[50];
    scanf(" %s",zilla);
    toUpperString(zilla);
    int destination_index = -1;
    char temp[20];
    for (int i = 0; i < NUM_DISTRICTS; i++)
    {
        strcpy(temp, districts[i]);
        toUpperString(temp);
        if (strcmp(temp, zilla) == 0)
        {
            destination_index = i;
            break;
        }
    }
    if (destination_index == -1)
    {
        printf("Name NOT Found , Check for Typo\n");
    }

    else
    {

        // Beautifully formatted algorithm labels
        printf("\n**************************************************\n");
        printf(" Algorithm 1: Dijkstra's Algorithm\n");
        printf("**************************************************\n");
        dijkstra(graph, 0, destination_index);
        getchar();
        system("cls");
        printf("\n**************************************************\n");
        printf(" Algorithm 2: Bellman's Algorithm\n");
        printf("**************************************************\n");
        bellmanFord(graph, 0, destination_index);
        printf("Press enter to continue...........");
        getchar();
        system("cls");
        printf("\n**************************************************\n");
        printf(" Algorithm 3: Nearest Neighbors Algorithm\n");
        printf("**************************************************\n");
        nearestNeighbors(graph, 0, destination_index);
        printf("Press enter to continue...........");

    }
}
void display_menu()
{
    // Beautifully formatted menu options
    printf("\n**************************************************\n");
    printf("          Choose an Option:\n");
    printf("**************************************************\n");
    printf(" [1] Distance From DSC\n");
    printf(" [2] Print All Districts\n");
    printf("**************************************************\n");

}
void print_all()
{
    for(int i = 0; i<64-1; i++)
    {
        for(int j = 0; j<64-1-i; j++)
        {
            if(strcmp(district2[j],district2[j+1])>0)
            {
                char temp[50];
                strcpy(temp,district2[j]);
                strcpy(district2[j],district2[j+1]);
                strcpy(district2[j+1],temp);
            }
        }
    }
    printf("ALL DISTRICTS\n");
    for(int i =0; i<64; i++)
    {
        printf("[%d] %s\n",i+1,district2[i]);
    }
    clear();
}
void clear()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
