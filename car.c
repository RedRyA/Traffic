#include <stdio.h>
#include <stdlib.h>
#include "car.h"
#include "utils.h"

Car* front = NULL;
Car* rear = NULL;

Car* createNewCarRand(int maxpoint) {
    int startPoint = getRandomPoint(maxpoint);
    int endPoint;
    do {
        endPoint = getRandomPoint(maxpoint);
    } while (endPoint == startPoint);

    Car* newCar = malloc(sizeof(Car));
    if (!newCar) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    newCar->start = startPoint;
    newCar->destination = endPoint;
    newCar->next = NULL;
    return newCar;
}

void enqueueCar(int maxpoint) {
    Car* newCar = createNewCarRand(maxpoint);
    if (!newCar) return;

    if (rear == NULL) {
        front = rear = newCar;
    } else {
        rear->next = newCar;
        rear = newCar;
    }

    carDequeue();
}

void enqueueMultipleCars(int numCars, int maxPoint) {
    for (int i = 0; i < numCars; i++) {
        enqueueCar(maxPoint);
    }
}

void carDequeue() {
    if (front == NULL) {
        printf("No cars in queue\n");
        return;
    }

    Car* temp = front;
    printf("Car from %d to %d is leaving the queue\n", temp->start, temp->destination);
    front = front->next;
    if (front == NULL) rear = NULL;
    free(temp);
}

void moveCar(Car* car) {
    if (car->pathLength > 0) {
        car->start = car->path[0];
    }
}

void printGraphStatus(Graph* graph, Car cars[], int carCount) {
    for (int i = 0; i < carCount; i++) {
        printf("🚗 Car %d at %s ➡️ %s\n", i,
               graph->nodeNames[cars[i].start],
               graph->nodeNames[cars[i].destination]);
    }
}