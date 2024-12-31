#include <stdio.h>
#include <assert.h>

#include "elevator.h"
// #include "events_from_elevator.h"
#include "controls_to_elevator.h"

#include "elevatorController.h"

// these variables can be written / read by another thread,
// thus the volatile qualifier
static volatile unsigned int elapsedTime; // seconds
static volatile unsigned int power;       // 0 is off 1 is on
static volatile unsigned int cabPosition; // 20 to 40.  20 is the second floor,
                                          // 30 is the third floor, etc.
static volatile int cabDirection;         // -1 is down, +1 is up.  and 0 is neither
static volatile int doorPosition;         // 0 is open, 5 is fully closed
static volatile int doorDirection;        // -1 is closing, +1 is opening, 0 is not moving

const char *ElevatorControlsEnumName(ElevatorControlsEnum e)
{
        const char *n[] = {"POWER_ON", "GO_UP", "GO_DOWN", "STOP", "OPEN_DOOR", "CLOSE_DOOR"};
        return n[e];
}

void elevator_control(ElevatorControlsEnum e, int on)
{
        printf("elevator_control received by the elevator %s\n", ElevatorControlsEnumName(e));
        // controls to the elevator are recieved here
        switch (e)
        {
        case POWER_ON:
                break;
        case GO_UP:
                cabDirection = on ? 1 : 0;
                break;
        case GO_DOWN:
                cabDirection = on ? -1 : 0;
                break;
        case STOP:
                cabDirection = on ? 0 : cabDirection;
                break;
        case OPEN_DOOR:
                doorDirection = on ? 1 : 0;
                break;
        case CLOSE_DOOR:
                doorDirection = on ? -1 : 0;
                break;
        default:
                assert(0);
        }
}

// void event_to_elevator(elevatorEventEnum e)
//{
//	// all events being sent to the elevator are received here.
// }

void init_elevator()
{
        // this function is called to initialize the simulated elevator
        elapsedTime = 0;
        power = 0;
        cabPosition = 20; // ground floor
        cabDirection = 0; // not moving
        doorPosition = 5; // closed
        doorDirection = 0;
}

void elevator_tick()
{
        // printf("elevator tick called\n");
        if (power)
        {
                //////////////////////////////////////////////
                // move the time forward
                elapsedTime++;

                //////////////////////////////////////////////
                // move the cab, if so desired
                if (cabDirection == 0)
                {
                        // hang where we are
                }
                else if (cabDirection == 1)
                {
                        // going up
                        if (cabPosition < 40)
                        {
                                cabPosition++;
                        }
                }
                else if (cabDirection == -1)
                {
                        // going down
                        if (cabPosition > 20)
                        {
                                cabPosition--;
                        }
                }

                //////////////////////////////////////////////
                // deal with the door
                if (doorDirection == 0)
                {
                        ; // it is where it should be, and is not moving
                }
                else if (doorDirection == 1)
                {
                        if (doorDirection < 5)
                        {
                                doorPosition++;
                        }
                }
                else if (doorDirection == -1)
                {
                        if (doorPosition > 1)
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
                        if (doorPosition == 1)
                        {
                                event_to_controller(DOOR_IS_OPEN);
                        }
                        else if (doorPosition == 5)
                        {
                                event_to_controller(DOOR_IS_CLOSED);
                        }
                }
                // figure this out.... DOOR_IS_OBSTRUCTED();

                if (cabDirection)
                {
                        if (cabPosition == 20)
                        {
                                event_to_controller(CAB_POSITION_FLOOR_2);
                        }
                        else if (cabPosition == 25)
                        {
                                event_to_controller(CAB_POSITION_FLOOR_2_5);
                        }
                        else if (cabPosition == 30)
                        {
                                event_to_controller(CAB_POSITION_FLOOR_3);
                        }
                        else if (cabPosition == 35)
                        {
                                event_to_controller(CAB_POSITION_FLOOR_3_5);
                        }
                        else if (cabPosition == 40)
                        {
                                event_to_controller(CAB_POSITION_FLOOR_4);
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
                event_to_controller(POWER_ON);
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
