#ifndef CAR_H
#define CAR_H

#include "graph.h"

typedef struct Car {
    int start;
    int destination;
    int path[MAX_NODES];
    int pathLength;
    struct Car* next;
} Car;

void enqueueCar(int maxpoint);
void enqueueMultipleCars(int numCars, int maxPoint);
void carDequeue();
Car* createNewCarRand(int maxpoint);
void moveCar(Car* car);
void printGraphStatus(Graph* graph, Car cars[], int carCount);

#endif