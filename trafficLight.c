#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
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

//Function
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
// Start of main()
int main()
{
srand(time(NULL));  // Seed once at the start
enqueueMultipleCars(10,10);

timerFunc();
    Graph trafficGraph;
    initializeGraph(&trafficGraph);      // Set up node names + connections
    printGraph(&trafficGraph); 
    
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
findPath(&graph, newCar);

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
void initializeGraph(Graph* graph) {
    for (int i = 0; i < MAX_NODES; i++) {
        graph->nodeNames[i] = malloc(20);
        sprintf(graph->nodeNames[i], "Node %d", i);

        for (int j = 0; j < MAX_NODES; j++) {
            graph->adjacency[i][j] = (rand() % 2); // random connection
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
void dijkstra(Graph* graph, Car* car)
 {
int dist[MAX_NODES];
int prev[MAX_NODES];
bool visited[MAX_NODES] = false;

for (int i = 0; i<MAX_NODES; i++)
{
    dist[i] = INT_MAX;
    prev[i] = -1;

}
dist[car -> start] = 0;

for (i=0; i < MAX_NODES; i++){
int minDist = INT_MAX;
int u = -1;

       for (int j = 0; j < MAX_NODES; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
}
 if (u == -1) break;
        visited[u] = true;

           for (int v = 0; v < MAX_NODES; v++) {
            if (graph->adjacency[u][v] && !visited[v] && dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
                prev[v] = u;
            }
        }
          int tempPath[MAX_NODES];
    int len = 0;
    for (int at = car->destination; at != -1; at = prev[at]) {
        tempPath[len++] = at;
 
}
}
// make a graph
// map cars to graph
// path finding algo
// add emergency vehicle to queue
// add interrupt 