#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
// Make a timed traffic light
// use enum for light colors
// use array for time

// Lights
enum State {
RED,
YELLOW,
GREEN,
LIGHT_COUNT

};
enum State current = RED;
const char* stateNames[] = {"RED", "YELLOW", "GREEN"};

// graph 
#define MAX_NODES 10
typedef struct Graph {
    int adjacency[MAX_NODES][MAX_NODES];
    char* nodeNames[MAX_NODES];

    }Graph;
// cars
typedef struct Car {
    int start;
    int destination;
    int path[MAX_NODES];
    int pathLength;
    struct Car* next;
}Car;

Car* front = NULL;
Car* rear = NULL;
int carCount = 0;



int timer[]={2000,1400,1545};

//Functions
int timerFunc();
void sleepFunc(int x);
void changeLight();
int getRandomPoint(int max);
Car* createNewCarRand(int maxpoint);
void enqueueCar();
void enqueueMultipleCars (int numCars, int maxPoint);
void carDequeue ();
void moveCar(Car* car);
void printGraphStatus(Graph* graph, Car cars[], int carCount);
void initializeGraph(Graph* graph);
void printGraph(Graph* graph);
int minDistance(int dist[],int visited[]);
void dijkstra(int graph[MAX_NODES][MAX_NODES], int src);
void addEdge(Graph* graph, int from, int to, int we);
// Start of main()
int main()
{
srand(time(NULL));  // Seed once at the start
// change this to a RGN eventually
int numCars = 50;
enqueueMultipleCars(numCars,10);

timerFunc();
    Graph graph;
    initializeGraph(&graph); 
    dijkstra(graph.adjacency, 0);     // Set up node names + connections
    printGraph(&graph); 
    
}
// loops through timer array and passes to sleepFunc()
int timerFunc()
{
int count=sizeof(timer)/sizeof(timer[0]);
for(int t=0;t<count;t++){

int sleepCount=timer[t];
sleepFunc(sleepCount);
}
return 0;
}
// takes int x and uses in a sleep function 
void sleepFunc(int x)
{
//passes a delay to change a light
usleep(x);
changeLight();
}

// changes the Light
void changeLight()
{

current = (current +1) % LIGHT_COUNT;
printf("Light changed to: %s\n", stateNames[current]);


}
// generate Random Num
int getRandomPoint(int max) 
{
return rand() % max;

}
Car* createNewCarRand(int maxpoint)
{
int startPoint = getRandomPoint(maxpoint);
int endPoint;

do {
    endPoint = getRandomPoint(maxpoint);

} while (endPoint == startPoint);
Car* newCar = malloc(sizeof(Car));
if (!newCar) {
printf("Memory allocation failed");
return NULL;

}
   newCar->start = startPoint;
    newCar->destination = endPoint;
    newCar->next = NULL;

    return newCar;



}
// create a number of cars
void enqueueMultipleCars (int numCars, int maxPoint) 
{
    for (int i = 0; i < numCars; i++)
     {
        enqueueCar(maxPoint);  // Creates and enqueues one car
    }

}
// Enqueue
void enqueueCar(int maxpoint )
{
Car* newCar = createNewCarRand(maxpoint);


if (!newCar) return;

if (rear==NULL)
{
 front = rear = newCar;

} else {
        rear->next = newCar;
        rear = newCar;

}
carDequeue();

}

// Dequeue cars

void carDequeue ()
{
if  (front == NULL) {
printf("no cars in queue");
return;
}
Car* temp = front;
printf("Car from %d to %d is leaving the queue\n", temp ->start, temp->destination);
front = front ->next;
if (front == NULL) {
    rear = NULL;
}

free(temp);

}
// Move cars on graph
void moveCar(Car* car)
{
if (car->pathLength >0)
{
car -> start = car->path[0];

}


}
void printGraphStatus(Graph* graph, Car cars[], int carCount) {
    for (int i = 0; i < carCount; i++) {
        printf("🚗 Car %d at %s ➡️ %s\n", i,
               graph->nodeNames[cars[i].start],
               graph->nodeNames[cars[i].destination]);
    }
}

void addEdge(Graph* graph, int from, int to, int weight) {
    if (from >= 0 && from < MAX_NODES && to >= 0 && to < MAX_NODES && weight > 0) {
        graph->adjacency[from][to] = weight;
        graph->adjacency[to][from] = weight;  // If undirected
    }
}


void initializeGraph(Graph* graph) {
    for (int i = 0; i < MAX_NODES; i++) {
        graph->nodeNames[i] = malloc(20);
        sprintf(graph->nodeNames[i], "Node %d", i);

        for (int j = 0; j < MAX_NODES; j++) {
            graph->adjacency[i][j] = 0; // random connection
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
}
// make a graph
// map cars to graph
// path finding algo
// add emergency vehicle to queue
// add interrupt 