#include <stdio.h>

#include "elevator.h"

static unsigned int elapsedTime;
static unsigned int power;

void init_elevator()
{
    // this function is called at to initialize the simulated elevator
    elapsedTime = 0;
    power = 0;
}
void tick()
{
    printf("hello\n");
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
    init_elevator();
    power = 1;
}

void power_off()
{
    power = 0;
}

