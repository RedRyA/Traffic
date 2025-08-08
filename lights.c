#include <stdio.h>
#include <unistd.h>
#include "lights.h"

enum State current = RED;
const char* stateNames[] = {"RED", "YELLOW", "GREEN"};
int timer[] = {2000, 1400, 1545};

int timerFunc() {
    int count = sizeof(timer) / sizeof(timer[0]);
    for (int t = 0; t < count; t++) {
        sleepFunc(timer[t]);
    }
    return 0;
}

void sleepFunc(int x) {
    usleep(x);
    changeLight();
}

void changeLight() {
    current = (current + 1) % LIGHT_COUNT;
    printf("Light changed to: %s\n", stateNames[current]);
}