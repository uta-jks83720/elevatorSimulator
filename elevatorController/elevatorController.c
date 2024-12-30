#include <assert.h>
#include <stdio.h>

#include "elevatorController.h"


#include "controls_to_elevator.h"
#include "events_from_elevator.h"
#include "indicators.h"
#include "user_events.h"


// This is an example elevator controller.  As part of the
// assignment, students are to re-implement the elevator controller
// to meet the requirements (state diagram) of a previous assignment.
//
// This controller is limited in complexity, and is provided only to
// demonstrate a working system.
//
// Specifics of this sample controller:
//       1.  On power on, the elevator is initialized to the bottom floor (floor 2),
//           doors open.
//       2.  When a 'REQUEST' button is pressed, the elevator goes to that floor.
//       3.  When a 'CALL' button is pressed, the elevator goes to that floor. 
//       4.  REQUEST or CALL is acknowledged with a light.
//       4.  Once a CALL or a REQUEST is accepted, others are ignored until the elevator gets
//           to the desired floor.
//
//


// These functions are mandatory.  They must be implement with the same name and arguments
void controller_tick()
{

}
void controller_init()
{
}

void DOOR_IS_OPEN()
{
        printf("DOOR_IS_OPEN event\n");
}

void DOOR_IS_CLOSED()
{
        printf("DOOR_IS_CLOSED event\n");
}

void DOOR_IS_OBSTRUCTED()
{
        printf("DOOR_IS_OBSTRUCTED event\n");
}

void CAB_POSITION_FLOOR_2()
{
        printf("CAB_POSITION_FLOOR_2 event\n");
}

void CAB_POSITION_FLOOR_2_5()
{
        printf("CAB_POSITION_FLOOR_2_5 event\n");
}

void CAB_POSITION_FLOOR_3()
{
        printf("CAB_POSITION_FLOOR_3 event\n");
}

void CAB_POSITION_FLOOR_3_5()
{
        printf("CAB_POSITION_FLOOR_3_5 event\n");
}

void CAB_POSITION_FLOOR_4()
{
        printf("CAB_POSITION_FLOOR_4 event\n");
}

// The rest of these functions are not mandatory.  Students can implement the logic using 
// any design, however it must be using the C language.
//
typedef enum {OFF,FLOOR2,FLOOR3,FLOOR4,GOINGTO2,GOINGTO3,GOINGTO4} elevatorStateEnum;
static volatile elevatorStateEnum currentState;
char* elevatorStateEnumNames(elevatorStateEnum e)
{
	char *names[]= {"OFF","FLOOR2","FLOOR3","FLOOR4","GOINGTO2","GOINGTO3","GOINGTO4"};
	assert (e >=OFF || e <= GOINGTO4);
	return names[e];
}

void off_state_entry()
{
        currentState = OFF;
}

void floor2_state_entry()
{
        currentState = FLOOR2;
}

void floor3_state_entry()
{
        currentState = FLOOR3;
}

void floor4_state_entry()
{
        currentState = FLOOR4;
}

void goingto2_state_entry()
{
        currentState = GOINGTO2;
}

void goingto3_state_entry()
{
        currentState = GOINGTO3;
}

void goingto4_state_entry()
{
        currentState = GOINGTO4;
}

void (*fsm[8][GOINGTO4+1]) (void)={
                         {0,0,0,0,0,0,0}, // OFF
                         {0,0,0,0,0,0,0}, // FLOOR2
                         {0,0,0,0,0,0,0}, // FLOOR3
                         {0,0,0,0,0,0,0}, // FLOOR4
                         {0,0,0,0,0,0,0}, // GOINGTO2
                         {0,0,0,0,0,0,0}, // GOINGTO3
                         {0,0,0,0,0,0,0}, // GOINGTO4 
                       }; 

void transition(int eventNumber)
{
        if (fsm[eventNumber][currentState])
        {
             fsm[eventNumber][currentState]();
        }
}
