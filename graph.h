#ifndef GRAPH_H
#define GRAPH_H

#define MAX_NODES 10

typedef struct Graph {
    int adjacency[MAX_NODES][MAX_NODES];
    char* nodeNames[MAX_NODES];
} Graph;

void initializeGraph(Graph* graph);
void printGraph(Graph* graph);
void addEdge(Graph* graph, int from, int to, int weight);
void dijkstra(int graph[MAX_NODES][MAX_NODES], int src);
int minDistance(int dist[], int visited[]);

#endif