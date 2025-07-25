#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
// Make a timed traffic light
// use enum for light colors
// use array for time

enum State {
RED,
YELLOW,
GREEN,
LIGHT_COUNT


};
enum State current = RED;

int timer[]={2000,1400,1545,100,1029};

//Function
int timerFunc();
void sleepFunc(int x);
void changeLight();
int main()
{



timerFunc();






}
// loops through timer array and passes to sleepFunc()
int timerFunc()
{
int count=sizeof(timer)/sizeof(timer[0]);
for(int t=0;t<count;t++){
printf("%d\n",timer[t]);
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

void changeLight()
{

for(int i = 0; i<LIGHT_COUNT;i++)
{
printf("%d\n",current);


}


}