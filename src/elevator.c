#include <stdio.h>

#include "elevator.h"

// these variables can be written to by another thread,
// thus the volatile qualifier
static volatile unsigned int elapsedTime;
// seconds
static volatile unsigned int power;
// 0 is off 1 is on
static volatile unsigned int cabPosition;
// 20 to 40.  20 is the second floor, 30 is the third floor, etc.
static volatile int cabDirection;
// -1 is down, +1 is up.  and 0 is neither

void init_elevator()
{
    // this function is called to initialize the simulated elevator
    elapsedTime = 0;
    power = 0;
    cabPosition = 20; // ground floor
    cabDirection = 1; // not moving
}
void elevator_tick()
{
    printf("elevator tick called\n");
    printf("cab position %d\n",cabPosition);
    if (power)
    {
        // move the time forward
        elapsedTime++;

        // move the cab, if so desired
        if (cabDirection==0)
        {
            // hang where we are
        }
        else if (cabDirection==1)
        {
           // going up
            if (cabPosition<40)
            {
               cabPosition++;
            }
        }
        else if (cabDirection==-1)
        {
             // going down
             if (cabPosition>20)
             {
                cabPosition--;
             }
        }

        // generate any events for the elevator controller
        //
        //
        //
        //
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

int cab_position()
{
     return cabPosition;
}
