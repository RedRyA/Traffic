#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
#include "graph.h"
#include "car.h"
#include "lights.h"
#include "utils.h"


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