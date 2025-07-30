#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>



#define MAX_NODES 10


typedef struct Graph {
    int adjacency[MAX_NODES][MAX_NODES];
    char* nodeNames[MAX_NODES];

    }Graph;

void initializeGraph(Graph* graph);
void printGraph(Graph* graph);
int minDistance(int dist[],int visited[]);
void printSolution(int dist[]);
void dijkstra(int graph[MAX_NODES][MAX_NODES], int src);

//MAIN
int main() 
    {
Graph graph;
initializeGraph(&graph);
printGraph(&graph);
 dijkstra(graph.adjacency, 0);

return 0;
    }

    void initializeGraph(Graph* graph) {
    for (int i = 0; i < MAX_NODES; i++) {
        graph->nodeNames[i] = malloc(20);
        sprintf(graph->nodeNames[i], "Node %d", i);

        for (int j = 0; j < MAX_NODES; j++) {
            if (i==j){

                graph->adjacency[i][j]= 0;
            } else {

                     graph->adjacency[i][j] = (rand() % 10); // random connection
            }
       
        }
    }
}

void printGraph(Graph* graph) {
    printf("\n📍 Traffic Map (Adjacency Matrix):\n\n");
    
    // Print column headers
    printf("     ");
    for (int i = 0; i < MAX_NODES; i++) {
        printf("%3d ", i);
    }
    printf("\n");

    // Print rows with connections
    for (int i = 0; i < MAX_NODES; i++) {
        printf("%3d ", i);
        for (int j = 0; j < MAX_NODES; j++) {
            printf(" %2d ", graph->adjacency[i][j]);
        }
        printf(" | %s\n", graph->nodeNames[i]); // Show node name
    }
}

int minDistance(int dist[],int visited[])
{
    int min = INT_MAX, min_index;
    for (int i = 0; i < MAX_NODES; i++)
    {
        if (!visited[i] && dist[i] <=min)
        min=dist[i], min_index = i;
       
    }
 return min_index;


}

void printSolution(int dist[]) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < MAX_NODES; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}


void dijkstra(int graph[MAX_NODES][MAX_NODES], int src) {
    int dist[MAX_NODES];     // Output array
    int visited[MAX_NODES];  // Visited set

    for (int i = 0; i < MAX_NODES; i++)
        dist[i] = INT_MAX, visited[i] = 0;

    dist[src] = 0;

    for (int count = 0; count < MAX_NODES - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;

        for (int v = 0; v < MAX_NODES; v++)
            if (!visited[v] && graph[u][v] &&
                dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printSolution(dist);
}
