#include <stdio.h>

#include "elevator.h"

static volatile unsigned int elapsedTime;
static volatile unsigned int power;

void init_elevator()
{
    // this function is called at to initialize the simulated elevator
    elapsedTime = 0;
    power = 0;
}
void elevator_tick()
{
    printf("elevator tick called\n");
    if (power)
    {
        elapsedTime++;
    }
}

unsigned int timeInSeconds()
{
    return elapsedTime;
}

void power_on()
{
    printf("power on called\n");
    if (!power)
    {
       init_elevator();
       power = 1;
    }
}

void power_off()
{
    printf("power off called\n");
    power = 0;
}

int power_status()
{
        printf("power status called %d\n",power);
        return power;
}

