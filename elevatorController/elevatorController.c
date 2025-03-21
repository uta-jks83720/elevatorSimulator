#include <assert.h>
#include <stdio.h>

#include "debug.h"
#include "elevatorController.h"
#include "events.h"

// This is an example elevator controller.  As part of the
// assignment, students are to re-implement the elevator controller
// to meet the requirements (state diagram) of a previous assignment.

// This controller is limited in complexity, and is provided only to
// demonstrate a working system.
//
// Specifics of this sample controller:
//       1.  On power on, the elevator is initialized to the bottom floor (floor 2),
//           doors open.
//       2.  When a 'REQUEST' button is pressed, the elevator goes to that floor.
//       3.  When a 'CALL' button is pressed, the elevator goes to that floor.
//       4.  REQUEST or CALL is acknowledged with a light.
//       5.  Once a CALL or a REQUEST is accepted, others are ignored until the
//           elevator gets to the desired floor.

static volatile elevatorStateEnum currentState;
static volatile unsigned int timer;

// each state has an "on entry" function.
// the are declared here so they can be available in the
// forthcoming data table(s).
void off_entry();
void init_entry();
void floor2_state_entry();
void floor3_state_entry();
void floor4_state_entry();
void goingdnto2_state_entry();
void goingdnto3_state_entry();
void goingupto3_state_entry();
void goingupto4_state_entry();
// New state entry functions
void floor2_door_opening_entry();
void floor2_door_open_entry();
void floor2_door_closing_entry();
void floor2_door_closed_entry();
void floor3_door_opening_entry();
void floor3_door_open_entry();
void floor3_door_closing_entry();
void floor3_door_closed_entry();
void floor4_door_opening_entry();
void floor4_door_open_entry();
void floor4_door_closing_entry();
void floor4_door_closed_entry();
void moving_up_entry();
void moving_down_entry();
void cab_pos_2_5_entry();
void cab_pos_3_5_entry();

// array of function pointers, indexed by elevatorStateEnum
// must be in the same order as the enums are declared
void (*on_entry[CAB_POS_3_5 + 1])() = {off_entry,
									  init_entry,
									  floor2_state_entry,
									  floor3_state_entry,
									  floor4_state_entry,
									  goingupto3_state_entry,
									  goingdnto3_state_entry,
									  goingupto4_state_entry,
									  goingdnto2_state_entry,
									  // New state entry functions
    								floor2_door_opening_entry,
									floor2_door_open_entry,
									floor2_door_closing_entry,
									floor2_door_closed_entry,
									floor3_door_opening_entry,
									floor3_door_open_entry,
									floor3_door_closing_entry,
									floor3_door_closed_entry,
									floor4_door_opening_entry,
									floor4_door_open_entry,
									floor4_door_closing_entry,
									floor4_door_closed_entry,
									moving_up_entry,
									moving_down_entry,
									cab_pos_2_5_entry,
									cab_pos_3_5_entry};

void (*on_exit[CAB_POS_3_5 + 1])() = {NULL};

typedef struct
{
	elevatorStateEnum nextState;
} stateInfo_t;

#define f false
#define t true
#define NONE (-1)  // Meaning no transition
#define _
#define __
#define _________________
#define ____
#define _____
#define ______
#define _______
#define ________
#define _________
#define __________
#define ___________
#define ____________
#define _____________
#define ______________
#define _______________
#define ________________
#define _________________
//  if NULL, then there is no transition for that event while in that state.
//                    STATE           EVENT
const stateInfo_t fsm[CAB_POS_3_5 + 1][REQ_BELL_RELEASED + 1] = {
	/*              TIMER_EXPIRED     POWER ON         DOOR_IS_OPEN     DOOR_IS_CLOSED   DOOR_IS_OBSTRUCTED  CAB_POSITION_FLOOR_2   CAB_POSITION_FLOOR_2_5   CAB_POSITION_FLOOR_3 CAB_POSITION_FLOOR_3_5  CAB_POSITION_FLOOR_4   CALL_FLOOR_2      CALL_FLOOR_3     CALL_FLOOR_4      REQ_DOOR_OPEN      REQ_STOP     REQ_FLOOR_2      REQ_FLOOR_3      REQ_FLOOR_4     REQ_BELL_PRESSED   REQ_BELL_RELEASED*/
	/*OFF       */ {{NONE}, ___________{INIT}, _________{NONE}, __________{NONE}, __________{NONE}, ____________{NONE}, ______________{NONE}, _________________{NONE}, ______________{NONE}, _______________{NONE}, ______________{NONE}, ___________{NONE}, _______{NONE}, ___________{NONE}, ___________{NONE}, _______{NONE}, _______{NONE}, ________{NONE}, _________{NONE}, __________{NONE}},
	/*INIT      */ {{FLOOR2}, _________{NONE}, _________{NONE}, __________{NONE}, __________{NONE}, ____________{NONE}, ______________{NONE}, _________________{NONE}, ______________{NONE}, _______________{NONE}, ______________{NONE}, ___________{GOINGUPTO3}, _{GOINGUPTO4}, _____{NONE}, ___________{NONE}, _______{NONE}, _______{GOINGUPTO3}, __{GOINGUPTO4}, _________________{NONE}, __________{NONE}},
	/*FLOOR2    */ {{FLOOR2_DOOR_CLOSED}, ___________{NONE}, _________{NONE}, __________{NONE}, __________{NONE}, ____________{NONE}, ______________{NONE}, _________________{NONE}, ______________{NONE}, _______________{NONE}, ______________{NONE}, ___________{GOINGUPTO3}, _{GOINGUPTO4}, _____{NONE}, ___________{NONE}, _______{NONE}, _______{GOINGUPTO3}, __{GOINGUPTO4}, _________________{NONE}, __________{NONE}},
	/*FLOOR3    */ {{FLOOR3_DOOR_CLOSED}, ___________{NONE}, _________{NONE}, __________{NONE}, __________{NONE}, ____________{NONE}, ______________{NONE}, _________________{NONE}, ______________{NONE}, _______________{NONE}, ______________{GOINGDNTO2}, _____{NONE}, _______{GOINGUPTO4}, _____{NONE}, ___________{NONE}, _______{GOINGDNTO2}, _{NONE}, ________{GOINGUPTO4}, _________________{NONE}, __________{NONE}},
	/*FLOOR4    */ {{FLOOR4_DOOR_CLOSED}, ___________{NONE}, _________{NONE}, __________{NONE}, __________{NONE}, ____________{NONE}, ______________{NONE}, _________________{NONE}, ______________{NONE}, _______________{NONE}, ______________{GOINGDNTO2}, _____{GOINGDNTO3}, _{NONE}, ___________{NONE}, ___________{NONE}, _______{GOINGDNTO2}, _{GOINGDNTO3}, __{NONE}, _________{NONE}, __________{NONE}},
	/*GOINGUPTO3*/ {{NONE}, ___________{NONE}, _________{NONE}, __________{NONE}, __________{NONE}, ____________{NONE}, ______________{NONE}, _________________{FLOOR3}, ____________{NONE}, _______________{NONE}, ______________{NONE}, ___________{NONE}, _______{NONE}, ___________{NONE}, ___________{NONE}, _______{NONE}, _______{NONE}, ________{NONE}, _________{NONE}, __________{NONE}},
	/*GOINGDNTO3*/ {{NONE}, ___________{NONE}, _________{NONE}, __________{NONE}, __________{NONE}, ____________{NONE}, ______________{NONE}, _________________{FLOOR3}, ____________{NONE}, _______________{NONE}, ______________{NONE}, ___________{NONE}, _______{NONE}, ___________{NONE}, ___________{NONE}, _______{NONE}, _______{NONE}, ________{NONE}, _________{NONE}, __________{NONE}},
	/*GOINGUPTO4*/ {{NONE}, ___________{NONE}, _________{NONE}, __________{NONE}, __________{NONE}, ____________{NONE}, ______________{NONE}, _________________{NONE}, ______________{NONE}, _______________{FLOOR4}, ____________{NONE}, ___________{NONE}, _______{NONE}, ___________{NONE}, ___________{NONE}, _______{NONE}, _______{NONE}, ________{NONE}, _________{NONE}, __________{NONE}},
	/*GOINGDNTO2*/ {{NONE}, ___________{NONE}, _________{NONE}, __________{NONE}, __________{NONE}, ____________{FLOOR2}, ____________{NONE}, _________________{NONE}, ______________{NONE}, _______________{NONE}, ______________{NONE}, ___________{NONE}, _______{NONE}, ___________{NONE}, ___________{NONE}, _______{NONE}, _______{NONE}, ________{NONE}, _________{NONE}, __________{NONE}},
    /*FLOOR2_DOOR_OPENING*/ {{NONE}, _________________{NONE}, _________________{FLOOR2_DOOR_OPEN}, __{NONE}, __{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}},
    /*FLOOR2_DOOR_OPEN*/ {{FLOOR2_DOOR_CLOSING}, _________________{NONE}, _________________{NONE}, __{NONE}, __{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}},
    /*FLOOR2_DOOR_CLOSING*/ {{NONE}, _________________{NONE}, _________________{NONE}, __{FLOOR2_DOOR_CLOSED}, __{FLOOR2_DOOR_OPENING}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{FLOOR2_DOOR_OPENING}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}},
    /*FLOOR2_DOOR_CLOSED*/ {{NONE}, _________________{NONE}, _________________{FLOOR2}, __{NONE}, __{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{GOINGUPTO3}, _________________{GOINGUPTO4}, _________________{FLOOR2_DOOR_OPENING}, _________________{NONE}, _________________{NONE}, _________________{GOINGUPTO3}, _________________{GOINGUPTO4}, _________________{NONE}, _________________{NONE}},
    
    /*FLOOR3_DOOR_OPENING*/ {{NONE}, _________________{NONE}, _________________{FLOOR3_DOOR_OPEN}, __{NONE}, __{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}},
    /*FLOOR3_DOOR_OPEN*/ {{FLOOR3_DOOR_CLOSING}, _________________{NONE}, _________________{NONE}, __{NONE}, __{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}},
    /*FLOOR3_DOOR_CLOSING*/ {{NONE}, _________________{NONE}, _________________{NONE}, __{FLOOR3_DOOR_CLOSED}, __{FLOOR3_DOOR_OPENING}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{FLOOR3_DOOR_OPENING}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}},
    /*FLOOR3_DOOR_CLOSED*/ {{NONE}, _________________{NONE}, _________________{FLOOR3}, __{NONE}, __{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{GOINGDNTO2}, _________________{NONE}, _________________{GOINGUPTO4}, _________________{FLOOR3_DOOR_OPENING}, _________________{NONE}, _________________{GOINGDNTO2}, _________________{NONE}, _________________{GOINGUPTO4}, _________________{NONE}, _________________{NONE}},
    
    /*FLOOR4_DOOR_OPENING*/ {{NONE}, _________________{NONE}, _________________{FLOOR4_DOOR_OPEN}, __{NONE}, __{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}},
    /*FLOOR4_DOOR_OPEN*/ {{FLOOR4_DOOR_CLOSING}, _________________{NONE}, _________________{NONE}, __{NONE}, __{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}},
    /*FLOOR4_DOOR_CLOSING*/ {{NONE}, _________________{NONE}, _________________{NONE}, __{FLOOR4_DOOR_CLOSED}, __{FLOOR4_DOOR_OPENING}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{FLOOR4_DOOR_OPENING}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}},
    /*FLOOR4_DOOR_CLOSED*/ {{NONE}, _________________{NONE}, _________________{FLOOR4}, __{NONE}, __{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{GOINGDNTO2}, _________________{GOINGDNTO3}, _________________{NONE}, _________________{FLOOR4_DOOR_OPENING}, _________________{NONE}, _________________{GOINGDNTO2}, _________________{GOINGDNTO3}, _________________{NONE}, _________________{NONE}, _________________{NONE}},
    
    /*MOVING_UP*/ {{NONE}, _________________{NONE}, _________________{NONE}, __{NONE}, __{NONE}, _________________{FLOOR2}, _________________{CAB_POS_2_5}, _________________{FLOOR3}, _________________{CAB_POS_3_5}, _________________{FLOOR4}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}},
    /*MOVING_DOWN*/ {{NONE}, _________________{NONE}, _________________{NONE}, __{NONE}, __{NONE}, _________________{FLOOR2}, _________________{CAB_POS_2_5}, _________________{FLOOR3}, _________________{CAB_POS_3_5}, _________________{FLOOR4}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}},
    /*CAB_POS_2_5*/ {{NONE}, _________________{NONE}, _________________{NONE}, __{NONE}, __{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}},
    /*CAB_POS_3_5*/ {{NONE}, _________________{NONE}, _________________{NONE}, __{NONE}, __{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}, _________________{NONE}}
};
	


// after formatting the table, perhaps reading in a file would be easier.
// but, you can't beat looking at code compared to debugging it.

elevatorStateEnum transition(elevatorStateEnum state, eventEnum event)
{
	assert(state >= OFF && state <= CAB_POS_3_5);
	assert(event >= TIMER_EXPIRED && event <= REQ_BELL_RELEASED);

	elevatorStateEnum nextState = state;

	// run the "on entry" for the new state
	if (fsm[state][event].nextState !=NONE)
	{
		INFO_PRINT("current state = %s\n", elevatorStateEnumNames(state));

		// run the exit actions
		if (on_exit[state])
		{
			assert(on_entry[state]);
			(on_exit[state])();
		}

		// determine next state.
		nextState = fsm[state][event].nextState;
		assert(nextState >= OFF && nextState <= CAB_POS_3_5);

		INFO_PRINT("new state = %s\n", elevatorStateEnumNames(nextState));

		// run the entry actions
		if (on_entry[nextState])
		{
			assert(on_entry[nextState]);
			(on_entry[nextState])();
		}
	}

	return nextState;
}

void event_to_controller(eventEnum e)
{
	INFO_PRINT("event to controller %s\n", eventEnumName(e));
	// all events are processed in this function
	currentState = transition(currentState, e);
}

// These functions are mandatory.  They must be implement with the same name and arguments
void controller_tick()
{
	// DEBUG_PRINT("controller tick\n");
	//  this is where timers are handled
	if (timer)
	{
		timer--;
		if (!timer)
		{
			event_to_controller(TIMER_EXPIRED);
		}
	}
}

void controller_init()
{
	DEBUG_PRINT("\n");
	currentState = OFF;
	// clear all timers
	timer = 0;
}

// The functions below are unique to the specific state diagram

void init_entry()
{
	DEBUG_PRINT("\n");
	// as part of the requirements, the door needs to be opened
	// and all indicators turned on.
	elevator_control_cmd(OPEN_DOOR);
	elevator_indicators(-1);
	timer = 10;
}

void off_entry()
{
	DEBUG_PRINT("\n");
	int eCmd = ALL_OFF;
	elevator_control_cmd(eCmd);
}

void floor2_state_entry()
{
	DEBUG_PRINT("\n");
	elevator_control_cmd(ALL_OFF);
	elevator_indicators(CAB_POS_2 | POS_FLOOR_2);
	timer = 10;
}

void floor3_state_entry()
{
	DEBUG_PRINT("\n");
	elevator_control_cmd(ALL_OFF);
	elevator_indicators(CAB_POS_3 | POS_FLOOR_3);
	timer = 10;
}

void floor4_state_entry()
{
	DEBUG_PRINT("\n");
	elevator_control_cmd(ALL_OFF);
	elevator_indicators(CAB_POS_4 | POS_FLOOR_4);
	timer = 10;
}

void goingdnto2_state_entry()
{
	DEBUG_PRINT("\n");
	elevator_control_cmd(GO_DOWN);
	elevator_indicators(indicators() | REQ_FLOOR_ACCEPTED_2 | CALL_ACCEPTED_FLOOR_2 | UPPTAGEN_FLOOR_3 | UPPTAGEN_FLOOR_4);
}

void goingdnto3_state_entry()
{
	DEBUG_PRINT("\n");
	elevator_control_cmd(GO_DOWN);
	elevator_indicators(indicators() | REQ_FLOOR_ACCEPTED_3 | CALL_ACCEPTED_FLOOR_3 | UPPTAGEN_FLOOR_4 | UPPTAGEN_FLOOR_2);
}

void goingupto3_state_entry()
{
	DEBUG_PRINT("\n");
	elevator_control_cmd(GO_UP);
	elevator_indicators(indicators() | REQ_FLOOR_ACCEPTED_3 | CALL_ACCEPTED_FLOOR_3 | UPPTAGEN_FLOOR_2 | UPPTAGEN_FLOOR_4);
}

void goingupto4_state_entry()
{
	DEBUG_PRINT("\n");
	elevator_control_cmd(GO_UP);
	elevator_indicators(indicators() | REQ_FLOOR_ACCEPTED_4 | CALL_ACCEPTED_FLOOR_4 | UPPTAGEN_FLOOR_2 | UPPTAGEN_FLOOR_3);
}

// New state entry functions implementation based on state diagram
void floor2_door_opening_entry()
{
    DEBUG_PRINT("\n");
    elevator_control_cmd(OPEN_DOOR);
    elevator_indicators(indicators() | POS_FLOOR_2);
}

void floor2_door_open_entry()
{
    DEBUG_PRINT("\n");
    elevator_control_cmd(ALL_OFF);
    elevator_indicators(indicators() | POS_FLOOR_2);
    // Set timer to auto-close after a while
    timer = 5;
}

void floor2_door_closing_entry()
{
    DEBUG_PRINT("\n");
    elevator_control_cmd(CLOSE_DOOR);
    elevator_indicators(indicators() | POS_FLOOR_2);
}

void floor2_door_closed_entry()
{
    DEBUG_PRINT("\n");
    elevator_control_cmd(ALL_OFF);
    elevator_indicators(indicators() | POS_FLOOR_2);
}

void floor3_door_opening_entry()
{
    DEBUG_PRINT("\n");
    elevator_control_cmd(OPEN_DOOR);
    elevator_indicators(indicators() | POS_FLOOR_3);
}

void floor3_door_open_entry()
{
    DEBUG_PRINT("\n");
    elevator_control_cmd(ALL_OFF);
    elevator_indicators(indicators() | POS_FLOOR_3);
    // Set timer to auto-close after a while
    timer = 5;
}

void floor3_door_closing_entry()
{
    DEBUG_PRINT("\n");
    elevator_control_cmd(CLOSE_DOOR);
    elevator_indicators(indicators() | POS_FLOOR_3);
}

void floor3_door_closed_entry()
{
    DEBUG_PRINT("\n");
    elevator_control_cmd(ALL_OFF);
    elevator_indicators(indicators() | POS_FLOOR_3);
}

void floor4_door_opening_entry()
{
    DEBUG_PRINT("\n");
    elevator_control_cmd(OPEN_DOOR);
    elevator_indicators(indicators() | POS_FLOOR_4);
}

void floor4_door_open_entry()
{
    DEBUG_PRINT("\n");
    elevator_control_cmd(ALL_OFF);
    elevator_indicators(indicators() | POS_FLOOR_4);
    // Set timer to auto-close after a while
    timer = 5;
}

void floor4_door_closing_entry()
{
    DEBUG_PRINT("\n");
    elevator_control_cmd(CLOSE_DOOR);
    elevator_indicators(indicators() | POS_FLOOR_4);
}

void floor4_door_closed_entry()
{
    DEBUG_PRINT("\n");
    elevator_control_cmd(ALL_OFF);
    elevator_indicators(indicators() | POS_FLOOR_4);
}

void moving_up_entry()
{
    DEBUG_PRINT("\n");
    elevator_control_cmd(GO_UP);
    elevator_indicators(indicators());
}

void moving_down_entry()
{
    DEBUG_PRINT("\n");
    elevator_control_cmd(GO_DOWN);
    elevator_indicators(indicators());
}

void cab_pos_2_5_entry()
{
    DEBUG_PRINT("\n");
    // Intermediate floor position - maintain current direction
    elevator_indicators(indicators());
}

void cab_pos_3_5_entry()
{
    DEBUG_PRINT("\n");
    // Intermediate floor position - maintain current direction
    elevator_indicators(indicators());
}


// This function is important for debugging and is unique for the state diagram
const char *elevatorStateEnumNames(elevatorStateEnum e)
{
	assert(e >= OFF && e <= CAB_POS_3_5);
	const char *n[] = {"OFF",
					   "INIT",
					   "FLOOR2",
					   "FLOOR3",
					   "FLOOR4",
					   "GOINGUPTO3",
					   "GOINGDNTO3",
					   "GOINGUPTO4",
					   "GOINGDNTO2",
					   "FLOOR2_DOOR_OPENING",
						"FLOOR2_DOOR_OPEN",
						"FLOOR2_DOOR_CLOSING",
						"FLOOR2_DOOR_CLOSED",
						"FLOOR3_DOOR_OPENING",
						"FLOOR3_DOOR_OPEN",
						"FLOOR3_DOOR_CLOSING",
						"FLOOR3_DOOR_CLOSED",
						"FLOOR4_DOOR_OPENING",
						"FLOOR4_DOOR_OPEN",
						"FLOOR4_DOOR_CLOSING", 
						"FLOOR4_DOOR_CLOSED",
						"MOVING_UP",
						"MOVING_DOWN",
						"CAB_POS_2_5",
						"CAB_POS_3_5"};
	return n[e];
}
