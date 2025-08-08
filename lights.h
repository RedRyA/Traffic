#ifndef LIGHTS_H
#define LIGHTS_H

enum State { RED, YELLOW, GREEN, LIGHT_COUNT };
extern enum State current;

int timerFunc();
void sleepFunc(int x);
void changeLight();

#endif