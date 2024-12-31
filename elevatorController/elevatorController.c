#include <assert.h>
#include <stdio.h>

#include "elevatorController.h"



//#include "controls_to_elevator.h"
//#include "events_from_elevator.h"
//#include "indicators.h"
//#include "user_events.h"

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

static volatile elevatorStateEnum currentState;

char* elevatorStateEnumNames(elevatorStateEnum e)
{
	char *names[]= {"OFF","FLOOR2","FLOOR3","FLOOR4","GOINGUPTO3","GOINGDNTO3","GOINGUPTO4","GOINGDNTO2"};
	assert (e >=OFF || e <= GOINGDNTO2);
	return names[e];
}

// this function is used for debugging and test
char *controller_current_state()
{
	return elevatorStateEnumNames(currentState);
}


void off_state_entry();
void floor2_state_entry();
void floor3_state_entry();
void floor4_state_entry();
void goingdnto2_state_entry();
void goingdnto3_state_entry();
void goingupto3_state_entry();
void goingupto4_state_entry();

void (*on_entry[GOINGDNTO2+1])() = {off_state_entry,floor2_state_entry,floor3_state_entry,floor4_state_entry,goingdnto2_state_entry,goingdnto3_state_entry,goingupto3_state_entry,goingupto4_state_entry};

typedef struct 
{
    bool active;
	elevatorStateEnum nextState;
} stateInfo_t;

stateInfo_t fsm[GOINGDNTO2+1][CAB_POSITION_FLOOR_4+1]= {
	{ {true,OFF},{false,OFF},{false,OFF},{false,OFF},{false,OFF},{false,OFF},{false,OFF} },
	{ {false,FLOOR2},{false,POWER_ON},{false,POWER_ON},{false,POWER_ON},{false,POWER_ON},{false,POWER_ON},{false,POWER_ON} },
	{ {false,FLOOR3},{false,POWER_ON},{false,POWER_ON},{false,POWER_ON},{false,POWER_ON},{false,POWER_ON},{false,POWER_ON} },
	{ {false,FLOOR4},{false,POWER_ON},{false,POWER_ON},{false,POWER_ON},{false,POWER_ON},{false,POWER_ON},{false,POWER_ON} },
	{ {false,GOINGUPTO3},{false,GOINGUPTO3},{false,GOINGUPTO3},{false,GOINGUPTO3},{false,GOINGUPTO3},{false,GOINGUPTO3},{false,GOINGUPTO3} },
	{ {false,GOINGDNTO3},{false,GOINGDNTO3},{false,GOINGDNTO3},{false,GOINGDNTO3},{false,GOINGDNTO3},{false,GOINGDNTO3},{false,GOINGDNTO3} },
	{ {false,GOINGUPTO4},{false,POWER_ON},{false,POWER_ON},{false,POWER_ON},{false,POWER_ON},{false,POWER_ON},{false,POWER_ON} } 
                                                        };
elevatorStateEnum transition(elevatorStateEnum state, elevatorEventEnum event)
{
	assert (state >=OFF && state <= GOINGDNTO2);

    // determine next state.
    elevatorStateEnum nextState = fsm[state][event].nextState;

	assert (nextState >=OFF && nextState <= GOINGDNTO2);

    // run the on entry for the new state
    if (fsm[state][event].active)
    {
        if (on_entry[state])
        {
           printf("calling on_entry function\n");
           (on_entry[state]) ();
        }
     }

	printf("current state = %s",elevatorStateEnumNames(state));
	printf(" new state = %s",elevatorStateEnumNames(nextState));
	return nextState;
}

const char* elevatorEventEnumName (elevatorEventEnum e)
{
        const char* n[] = {"DOOR_IS_OPEN","DOOR_IS_CLOSED","DOOR_IS_OBSTRUCTED","CAB_POSITION_FLOOR_2","CAB_POSITION_FLOOR_2_5","CAB_POSITION_FLOOR_3","CAB_POSITION_FLOOR_3_5","CAB_POSITION_FLOOR_4"};
	return n[e];
}

void event_to_controller(elevatorEventEnum e)
{
	printf("in event to controller %s\n",elevatorEventEnumName(e));
}

// These functions are mandatory.  They must be implement with the same name and arguments
void controller_tick()
{
    // this is where timers are handled
}

void controller_init() // also the power on event
{
        printf("controller_init event\n");
	currentState = FLOOR2;
}


// The rest of these functions are not mandatory.  Students can implement the logic using 
// any design, however it must be using the C language.
//

/*
FLOOR2 : entry- GO_UP=F\n GO_DOWN=F\n OPEN_DOOR=F \n CLOSE_DOOR=F
FLOOR3 : entry- GO_UP=F\n GO_DOWN=F\n OPEN_DOOR=F \n CLOSE_DOOR=F
FLOOR4 : entry- GO_UP=F\n GO_DOWN=F\n OPEN_DOOR=F \n CLOSE_DOOR=F
GOINGUPTO3 : entry- GO_UP=T\n GO_DOWN=F\n OPEN_DOOR=F \n CLOSE_DOOR=F
GOINGDNTO3 : entry- GO_UP=F\n GO_DOWN=T\n OPEN_DOOR=F \n CLOSE_DOOR=F
GOINGUPTO4 : entry- GO_UP=T\n GO_DOWN=F\n OPEN_DOOR=F \n CLOSE_DOOR=F
GOINGDNTO2 : entry- GO_UP=F\n GO_DOWN=T\n OPEN_DOOR=F \n CLOSE_DOOR=F
FLOOR2 --> GOINGUPTO3 : CALL_FLOOR_3()
FLOOR2 --> GOINGUPTO4 : CALL_FLOOR_4()
FLOOR2 --> GOINGUPTO3 : REQ_FLOOR_3()
FLOOR2 --> GOINGUPTO4 : REQ_FLOOR_4()
FLOOR3 --> GOINGDNTO2 : CALL_FLOOR_2()
FLOOR3 --> GOINGUPTO4 : CALL_FLOOR_4()
FLOOR3 --> GOINGDNTO2 : REQCALL_FLOOR_2()
FLOOR3 --> GOINGUPTO4 : REQ_FLOOR_4()
FLOOR4 --> GOINGDNTO2 : CALL_FLOOR_2()
FLOOR4 --> GOINGDNTO2 : REQ_FLOOR_2()
FLOOR4 --> GOINGDNTO3 : CALL_FLOOR_3()
FLOOR4 --> GOINGDNTO3 : REQ_FLOOR_3()
GOINGDNTO2 -->FLOOR2 : CAB_POSITION_FLOOR_2()
GOINGDNTO3 -->FLOOR3 : CAB_POSITION_FLOOR_3()
GOINGUPTO3 -->FLOOR3 : CAB_POSITION_FLOOR_3()
GOINGUPTO4 -->FLOOR4 : CAB_POSITION_FLOOR_4()
*/


void off_state_entry()
{
	//assert(0);
}

void floor2_state_entry()
{
	elevator_control(GO_UP,0);
	elevator_control(GO_DOWN,0);
	elevator_control(OPEN_DOOR,0);
	elevator_control(CLOSE_DOOR,0);
}

void floor3_state_entry()
{
	elevator_control(GO_UP,0);
	elevator_control(GO_DOWN,0);
	elevator_control(OPEN_DOOR,0);
	elevator_control(CLOSE_DOOR,0);
}

void floor4_state_entry()
{
	elevator_control(GO_UP,0);
	elevator_control(GO_DOWN,0);
	elevator_control(OPEN_DOOR,0);
	elevator_control(CLOSE_DOOR,0);
}

void goingdnto2_state_entry()
{
	elevator_control(GO_UP,0);
	elevator_control(GO_DOWN,1);
	elevator_control(OPEN_DOOR,0);
	elevator_control(CLOSE_DOOR,0);
}

void goingdnto3_state_entry()
{
	elevator_control(GO_UP,0);
	elevator_control(GO_DOWN,1);
	elevator_control(OPEN_DOOR,0);
	elevator_control(CLOSE_DOOR,0);
}

void goingupto3_state_entry()
{
	elevator_control(GO_UP,1);
	elevator_control(GO_DOWN,0);
	elevator_control(OPEN_DOOR,0);
	elevator_control(CLOSE_DOOR,0);
}

void goingupto4_state_entry()
{
	elevator_control(GO_UP,1);
	elevator_control(GO_DOWN,0);
	elevator_control(OPEN_DOOR,0);
	elevator_control(CLOSE_DOOR,0);
}
