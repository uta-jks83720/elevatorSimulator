#include <stdio.h>

#include "elevator.h"
#include "events_from_elevator.h"


// these variables can be written to by another thread,
// thus the volatile qualifier
static volatile unsigned int elapsedTime; // seconds
static volatile unsigned int power;       // 0 is off 1 is on
static volatile unsigned int cabPosition; // 20 to 40.  20 is the second floor,
                                          // 30 is the third floor, etc.
static volatile int cabDirection;         // -1 is down, +1 is up.  and 0 is neither
static volatile int doorPosition;         // 0 is open, 5 is fully closed
static volatile int doorDirection;        // -1 is closing, +1 is opening, 0 is not moving

void init_elevator()
{
        // this function is called to initialize the simulated elevator
        elapsedTime = 0;
        power = 0;
        cabPosition = 20; // ground floor
        cabDirection = 1; // not moving
        doorPosition = 5; // closed
        doorDirection = 0;
}

void elevator_tick()
{
    //printf("elevator tick called\n");
    if (power)
    {
        //////////////////////////////////////////////
        // move the time forward
        elapsedTime++;

        //////////////////////////////////////////////
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

        //////////////////////////////////////////////
        // deal with the door
        if (doorDirection==0)
        {
        }
        else if (doorDirection==1)
        {
           if (doorDirection<5)
           {
               doorPosition++;
           }
        }
        else if (doorDirection==-1)
        {
           if (doorPosition>1)
           {
              doorPosition--;
           }
        }




        //////////////////////////////////////////////
        // generate any events for the elevator controller
        // these events are only generated once, each time they 
        // occur
        if (doorDirection)
        {
                if (doorPosition==1)
                {
                        DOOR_IS_OPEN();
                }
                else if (doorPosition==5)
                {
                        DOOR_IS_CLOSED();
                }
        }
        // figure this out.... DOOR_IS_OBSTRUCTED();

        if (cabDirection)
        {
                if (cabPosition == 20)
                {
                        CAB_POSITION_FLOOR_2();
                }
                else if (cabPosition == 25)
                {
                        CAB_POSITION_FLOOR_2_5();
                }
                else if (cabPosition == 30)
                {
                        CAB_POSITION_FLOOR_3();
                }
                else if (cabPosition == 35)
                {
                        CAB_POSITION_FLOOR_3_5();
                }
                else if (cabPosition == 40)
                {
                        CAB_POSITION_FLOOR_4();
                }       
        } // cab is moving

    } // power is on
}

unsigned int timeInSeconds()
{
        return elapsedTime;
}

void power_on()
{
        if (!power)
        {
                init_elevator();
                power = 1;
        }
}

void power_off()
{
        power = 0;
}

int power_status()
{
        return power;
}

int cab_position()
{
        return cabPosition;
}
