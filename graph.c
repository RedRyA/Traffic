#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

void addEdge(Graph* graph, int from, int to, int weight) {
    if (from >= 0 && from < MAX_NODES && to >= 0 && to < MAX_NODES && weight > 0) {
        graph->adjacency[from][to] = weight;
        graph->adjacency[to][from] = weight;
    }
}

void initializeGraph(Graph* graph) {
    for (int i = 0; i < MAX_NODES; i++) {
        graph->nodeNames[i] = malloc(20);
        sprintf(graph->nodeNames[i], "Node %d", i);
        for (int j = 0; j < MAX_NODES; j++) {
            graph->adjacency[i][j] = 0;
        }
    }
    addEdge(graph, 0, 9, 5);
    addEdge(graph, 1, 3, 2);
    addEdge(graph, 2, 6, 4);
    addEdge(graph, 3, 7, 3);
    addEdge(graph, 4, 5, 1);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 2);
    addEdge(graph, 7, 8, 3);
    addEdge(graph, 8, 9, 4);
}

void printGraph(Graph* graph) {
    printf("\n📍 Traffic Map (Adjacency Matrix):\n\n");
    printf("     ");
    for (int i = 0; i < MAX_NODES; i++) {
        printf("%3d ", i);
    }
    printf("\n");

    for (int i = 0; i < MAX_NODES; i++) {
        printf("%3d ", i);
        for (int j = 0; j < MAX_NODES; j++) {
            printf(" %2d ", graph->adjacency[i][j]);
        }
        printf(" | %s\n", graph->nodeNames[i]);
    }
}

int minDistance(int dist[], int visited[]) {
    int min = INT_MAX, min_index = -1;
    for (int i = 0; i < MAX_NODES; i++) {
        if (!visited[i] && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void dijkstra(int graph[MAX_NODES][MAX_NODES], int src) {
    int dist[MAX_NODES];
    int visited[MAX_NODES];

    for (int i = 0; i < MAX_NODES; i++)
        dist[i] = INT_MAX, visited[i] = 0;

    dist[src] = 0;

    for (int count = 0; count < MAX_NODES - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;

        for (int v = 0; v < MAX_NODES; v++) {
            if (!visited[v] && graph[u][v] &&
                dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}