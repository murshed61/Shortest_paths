#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define INF 9999999
#define NUM_DISTRICTS 9
#define TIME 5


char *murshed_paths[] = {"DSC", "Khagan", "Uttara", "Kuril", "Mothijheel", "Kanchpur", "Meghna", "Gouripur", "Titas"};
int murshed_costs[9][9] =
{
    {0, 5, 12, INF, INF, INF, INF, INF, INF},
    {5, 0, 11, INF, INF, INF, INF, INF, INF},
    {12, 11, 0, 8, 15, INF, INF, INF, INF},
    {INF, INF, 8, 0, 10, 20, INF, INF, INF},
    {INF, INF, 15, 10, 0, 5, 18, INF, INF},
    {INF, INF, INF, 20, 5, 0, 7, 25, INF},
    {INF, INF, INF, INF, 18, 7, 0, 12, 22},
    {INF, INF, INF, INF, INF, 25, 12, 0, 9},
    {INF, INF, INF, INF, INF, INF, 22, 9, 0}
};


char *Tanzina_paths[] = {"DSC", "Khagan", "Ashulia", "Ponchoboti", "Khalpar", "Runway City", "Jashim Uddin", "RailGate", "Ashkona"};
int Tanzina_costs[9][9] =
{
    {0, 4, INF, INF, INF, INF, INF, INF, INF},
    {4, 0, 6, 12, INF, INF, INF, INF, INF},
    {INF, 6, 0, 8, 9, INF, INF, INF, INF},
    {INF, 12, 8, 0, 5, 7, INF, INF, INF},
    {INF, INF, 9, 5, 0, 6, 10, INF, INF},
    {INF, INF, INF, 7, 6, 0, 4, 9, INF},
    {INF, INF, INF, INF, 10, 4, 0, 3, 11},
    {INF, INF, INF, INF, INF, 9, 3, 0, 8},
    {INF, INF, INF, INF, INF, INF, 11, 8, 0}
};


char *salman_paths[] = {"DSC", "Hemayetpur", "Nobinagar", "Mawa", "Shibchar", "Faridpur", "Magura", "Jhenaidah", "Chuadanga"};
int salman_costs[9][9] =
{
    {0, 3, INF, INF, INF, INF, INF, INF, INF},
    {3, 0, 5, INF, INF, INF, INF, INF, INF},
    {INF, 5, 0, 7, INF, INF, INF, INF, INF},
    {INF, INF, 7, 0, 10, INF, INF, INF, INF},
    {INF, INF, INF, 10, 0, 9, INF, INF, INF},
    {INF, INF, INF, INF, 9, 0, 6, INF, INF},
    {INF, INF, INF, INF, INF, 6, 0, 8, INF},
    {INF, INF, INF, INF, INF, INF, 8, 0, 4},
    {INF, INF, INF, INF, INF, INF, INF, 4, 0}
};


char *jishan_paths[] = {"DSC", "Khagan", "Ashulia", "Birulia", "Panchoboti", "Beribadh", "Metro Center", "Mirpur 10", "Mirpur 1"};
int jishan_costs[9][9] =
{
    {0, 2, INF, INF, INF, INF, INF, INF, INF},
    {2, 0, 3, INF, INF, INF, INF, INF, INF},
    {INF, 3, 0, 4, INF, INF, INF, INF, INF},
    {INF, INF, 4, 0, 6, INF, INF, INF, INF},
    {INF, INF, INF, 6, 0, 7, INF, INF, INF},
    {INF, INF, INF, INF, 7, 0, 5, INF, INF},
    {INF, INF, INF, INF, INF, 5, 0, 3, INF},
    {INF, INF, INF, INF, INF, INF, 3, 0, 2},
    {INF, INF, INF, INF, INF, INF, INF, 2, 0}
};


char *tazim_paths[] = {"DSC", "Khagan", "Birulia Bridge", "Ashulia", "Nabinagar", "Chandra", "Kaliakair", "Mirzapur", "Tangail"};
int tazim_costs[9][9] =
{
    {0, 4, INF, INF, INF, INF, INF, INF, INF},
    {4, 0, 3, INF, INF, INF, INF, INF, INF},
    {INF, 3, 0, 5, INF, INF, INF, INF, INF},
    {INF, INF, 5, 0, 6, INF, INF, INF, INF},
    {INF, INF, INF, 6, 0, 7, INF, INF, INF},
    {INF, INF, INF, INF, 7, 0, 8, INF, INF},
    {INF, INF, INF, INF, INF, 8, 0, 9, INF},
    {INF, INF, INF, INF, INF, INF, 9, 0, 10},
    {INF, INF, INF, INF, INF, INF, INF, 10, 0}
};
typedef struct per
{
    char *name;
    char **paths;
    int **costs;
} Person;

Person member[5] =
{
    {"Murshed", murshed_paths, murshed_costs},
    {"Tanzina", Tanzina_paths, Tanzina_costs},
    {"Salman", salman_paths, salman_costs},
    {"Jishan", jishan_paths, jishan_costs},
    {"Tazim", tazim_paths, tazim_costs}
};

int bellmanFord(int graph[NUM_DISTRICTS][NUM_DISTRICTS], int src, int dest, int index);
int dijkstra(int graph[NUM_DISTRICTS][NUM_DISTRICTS], int src, int dest, int index);
void printPath(int parent[], int dest, int index);
void toUpperString(char str[]);
int findMinDistance(int dist[], int visited[]);
void nearestNeighbors(int graph[NUM_DISTRICTS][NUM_DISTRICTS], int src, int dest, int index);
int findNearestNeighbor(int graph[NUM_DISTRICTS][NUM_DISTRICTS], int current, int visited[]);
void clear();

void toUpperString(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper(str[i]);
    }
}
int main()
{
    while(1)
    {
        system("cls");
        printf("OUR TEAM MEMBERS\n");
        printf("[Murshed] - 336\n");
        printf("[Tanzina] - 296\n");
        printf("[Salman] - 404\n");
        printf("[Jishan] - 152\n");
        printf("[Tazim] - 783\n");
        printf("Whose route's do you want to check?\n");
        printf("--> ");
        char name[20];
        scanf(" %s", name);
        char temp[20];
        toUpperString(name);
        int found = 0;
        for (int i = 0; i < 5; i++)
        {

            strcpy(temp, member[i].name);
            toUpperString(temp);
            if (strcmp(temp, name) == 0)
            {
                system("cls");
                printf("\n===============================================\n");
                printf(" For %s, We Can Find The Shortest Path\n", name);
                printf("===============================================\n");
                printf("\n==========================================\n");
                printf("    Using Bellman-Ford Algorithm\n");
                printf("==========================================\n");
                bellmanFord(member[i].costs, 0, 8, i);


                system("cls");
                printf("\n===============================================\n");
                printf(" For %s, We Can Find The Shortest Path\n", name);
                printf("===============================================\n");
                printf("\n==========================================\n");
                printf("    Dijkstra's Algorithm\n");
                printf("==========================================\n");
                dijkstra(member[i].costs, 0, 8, i);


                system("cls");
                printf("\n===============================================\n");
                printf(" For %s, We Can Find The Shortest Path\n", name);
                printf("===============================================\n");
                printf("\n==========================================\n");
                printf("    Using Nearest Neighbors Algorithm\n");
                printf("==========================================\n");
                nearestNeighbors(member[i].costs,0,8,i);
                found=1;
            }
        }
        if(!found)
        {
            printf("NOT FOUND , PLEASE INPUT NAME PROPERLY\n");
            clear();
            getchar();
        }

    }
}
int bellmanFord(int graph[NUM_DISTRICTS][NUM_DISTRICTS], int src, int dest, int index)
{
    int dist[NUM_DISTRICTS];
    int parent[NUM_DISTRICTS];


    for (int i = 0; i < NUM_DISTRICTS; i++)
    {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[src] = 0;


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


    for (int u = 0; u < NUM_DISTRICTS; u++)
    {
        for (int v = 0; v < NUM_DISTRICTS; v++)
        {
            if (graph[u][v] != INF && dist[u] + graph[u][v] < dist[v])
            {
                printf("Graph contains a negative-weight cycle!\n");
                return -1;
            }
        }
    }


    if (dist[dest] == INF)
    {
        printf("No path exists from %d to %d.\n", src, dest);
        return -1;
    }
    else
    {

        printf("\n-------------------------------------------\n");
        printf("Shortest distance from %s to %s: %d\n", member[index].paths[src], member[index].paths[dest], dist[dest]);
        printf("-------------------------------------------\n");

        printf("Path taken: ");
        printPath(parent, dest, index);
        printf("\n-------------------------------------------\n");
        clear();
        printf("Press Enter To continue......\n");
        getchar();
    }
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
int dijkstra(int graph[NUM_DISTRICTS][NUM_DISTRICTS], int src, int dest, int index)
{
    int dist[NUM_DISTRICTS];
    int visited[NUM_DISTRICTS] = {0};
    int parent[NUM_DISTRICTS];

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

    printf("\n***********************************************\n");
    printf(" Total Distance from Node %s to %s: %d\n", member[index].paths[src], member[index].paths[dest], dist[dest]);
    printf("***********************************************\n");
    printf("Path taken: ");
    printPath(parent, dest, index);

    printf("\n-------------------------------------------\n");
    printf("Press Enter To continue......\n");
    getchar();
    return dist[dest];
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
void nearestNeighbors(int graph[NUM_DISTRICTS][NUM_DISTRICTS], int src, int dest, int index)
{
    int visited[NUM_DISTRICTS] = {0};
    int current = src;
    int path[NUM_DISTRICTS];
    int pathIndex = 0;
    int totalDistance = 0;

    visited[current] = 1;
    path[pathIndex++] = current;

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


    printf("\n***********************************************\n");
    printf(" Total Distance from Node %s to %s: %d\n", member[index].paths[src], member[index].paths[dest], totalDistance);
    printf("***********************************************\n");

    printf("Path taken: ");
    for (int i = 0; i < pathIndex; i++)
    {
        printf(" %s->", member[index].paths[path[i]]);
    }
    printf("\n");
    printf("-------------------------------------------\n");
    printf("Press Enter To continue......\n");
    getchar();
}
void printPath(int parent[], int dest, int index)
{
    if (parent[dest] == -1)
    {
        printf("%s", member[index].paths[dest]);
        return;
    }
    printPath(parent, parent[dest], index);
    printf("->%s", member[index].paths[dest]);
}
void clear()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
