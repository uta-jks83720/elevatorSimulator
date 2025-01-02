#include <assert.h>
#include <stdio.h>

#include "debug.h"
#include "elevatorController.h"

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

// each state has an "on entry" function.
// the are declared here so they can be available in the
// forthcoming data table(s).
void off_state_entry();
void floor2_state_entry();
void floor3_state_entry();
void floor4_state_entry();
void goingdnto2_state_entry();
void goingdnto3_state_entry();
void goingupto3_state_entry();
void goingupto4_state_entry();

// array of function pointers, indexed by elevatorStateEnum
void (*on_entry[GOINGDNTO2 + 1])() = {off_state_entry, floor2_state_entry, floor3_state_entry, floor4_state_entry, goingdnto2_state_entry, goingdnto3_state_entry, goingupto3_state_entry, goingupto4_state_entry};

typedef struct
{
	bool active; // this entry is ignored if active is false
	elevatorStateEnum nextState;
} stateInfo_t;

#define f false
#define t true
#define _
#define __
#define ___
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

//                    STATE           EVENT
const stateInfo_t fsm[GOINGDNTO2 + 1][REQ_BELL_RELEASED + 1] = {
	/*              DOOR_IS_OPEN     DOOR_IS_CLOSED   DOOR_IS_OBSTRUCTED  CAB_POSITION_FLOOR_2   CAB_POSITION_FLOOR_2_5   CAB_POSITION_FLOOR_3   CAB_POSITION_FLOOR_3_5  CAB_POSITION_FLOOR_4   CALL_FLOOR_2      CALL_FLOOR_3     CALL_FLOOR_4      REQ_DOOR_OPEN      REQ_STOP        REQ_FLOOR_2      REQ_FLOOR_3          REQ_FLOOR_4        REQ_BELL_PRESSED   REQ_BELL_RELEASED*/
	/*OFF       */ {{t, OFF}, _______{f, OFF}, _______{f, OFF}, __________{f, OFF}, _____________{f, OFF}, ______________{f, OFF}, ______________{f, OFF}, _____________{f, OFF}, ______________{f, OFF}, ________{f, OFF}, _______{f, OFF}, ________{f, OFF}, ________{f, OFF}, _______{f, OFF}, _______{f, OFF}, ___________{f, OFF}, ________{f, OFF}, __________{f, OFF}},
	/*FLOOR2    */ {{f, FLOOR2}, ____{f, FLOOR2}, ____{f, FLOOR2}, _______{f, FLOOR2}, __________{f, FLOOR2}, ___________{f, FLOOR2}, ___________{f, FLOOR2}, __________{f, FLOOR2}, ___________{f, FLOOR2}, _____{t, GOINGUPTO3}, {t, GOINGUPTO4}, _{f, FLOOR2}, _____{f, FLOOR2}, ____{f, FLOOR2}, ____{t, GOINGUPTO3}, ____{t, GOINGUPTO4}, _{f, FLOOR2}, _______{f, FLOOR2}},
	/*FLOOR3    */ {{f, FLOOR3}, ____{f, FLOOR3}, ____{f, FLOOR3}, _______{f, FLOOR3}, __________{f, FLOOR3}, ___________{f, FLOOR3}, ___________{f, FLOOR3}, __________{f, FLOOR3}, ___________{t, GOINGDNTO2}, _{f, FLOOR3}, ____{t, GOINGUPTO4}, _{f, FLOOR3}, _____{f, FLOOR3}, ____{t, GOINGDNTO2}, {f, FLOOR3}, ________{t, GOINGUPTO4}, _{f, FLOOR3}, _______{f, FLOOR3}},
	/*FLOOR4    */ {{f, FLOOR4}, ____{f, FLOOR4}, ____{f, FLOOR4}, _______{f, FLOOR4}, __________{f, FLOOR4}, ___________{f, FLOOR4}, ___________{f, FLOOR4}, __________{f, FLOOR4}, ___________{t, GOINGDNTO2}, _{t, GOINGDNTO3}, {f, FLOOR4}, _____{f, FLOOR4}, _____{f, FLOOR4}, ____{t, GOINGDNTO2}, {t, GOINGDNTO3}, ____{f, FLOOR4}, _____{f, FLOOR4}, _______{f, FLOOR4}},
	/*GOINGUPTO3*/ {{f, GOINGUPTO3}, {f, GOINGUPTO3}, {f, GOINGUPTO3}, ___{f, GOINGUPTO3}, ______{f, GOINGUPTO3}, _______{t, FLOOR3}, ___________{f, GOINGUPTO3}, ______{f, GOINGUPTO3}, _______{f, GOINGUPTO3}, _{f, GOINGUPTO3}, {f, GOINGUPTO3}, _{f, GOINGUPTO3}, _{f, GOINGUPTO3}, {f, GOINGUPTO3}, {f, GOINGUPTO3}, ____{f, GOINGUPTO3}, _{f, GOINGUPTO3}, ___{f, GOINGUPTO3}},
	/*GOINGDNTO3*/ {{f, GOINGDNTO3}, {f, GOINGDNTO3}, {f, GOINGDNTO3}, ___{f, GOINGDNTO3}, ______{f, GOINGDNTO3}, _______{t, FLOOR3}, ___________{f, GOINGDNTO3}, ______{f, GOINGDNTO3}, _______{f, GOINGDNTO3}, _{f, GOINGDNTO3}, {f, GOINGDNTO3}, _{f, GOINGDNTO3}, _{f, GOINGDNTO3}, {f, GOINGDNTO3}, {f, GOINGDNTO3}, ____{f, GOINGDNTO3}, _{f, GOINGDNTO3}, ___{f, GOINGDNTO3}},
	/*GOINGUPTO4*/ {{f, GOINGUPTO4}, {f, GOINGUPTO4}, {f, GOINGUPTO4}, ___{f, GOINGUPTO4}, ______{f, GOINGUPTO4}, _______{f, GOINGUPTO4}, _______{f, GOINGUPTO4}, ______{t, FLOOR4}, ___________{f, GOINGUPTO4}, _{f, GOINGUPTO4}, {f, GOINGUPTO4}, _{f, GOINGUPTO4}, _{f, GOINGUPTO4}, {f, GOINGUPTO4}, {f, GOINGUPTO4}, ____{f, GOINGUPTO4}, _{f, GOINGUPTO4}, ___{f, GOINGUPTO4}},
	/*GOINGDNTO2*/ {{f, GOINGDNTO2}, {f, GOINGDNTO2}, {f, GOINGDNTO2}, ___{t, FLOOR2}, __________{f, GOINGDNTO2}, _______{f, GOINGDNTO2}, _______{f, GOINGDNTO2}, ______{f, GOINGDNTO2}, _______{f, GOINGDNTO2}, _{f, GOINGDNTO2}, {f, GOINGDNTO2}, _{f, GOINGDNTO2}, _{f, GOINGDNTO2}, {f, GOINGDNTO2}, {f, GOINGDNTO2}, ____{f, GOINGDNTO2}, _{f, GOINGDNTO2}, ___{f, GOINGDNTO2}}};

// after formatting the table, perhaps reading in a file would be easier.
// but, you can't beat looking at code compared to debugging it.

elevatorStateEnum transition(elevatorStateEnum state, eventEnum event)
{
	assert(state >= OFF && state <= GOINGDNTO2);
	assert(event >= DOOR_IS_OPEN && event <= REQ_BELL_RELEASED);

	elevatorStateEnum nextState = state;

	// run the "on entry" for the new state
	if (fsm[state][event].active)
	{
		// determine next state.
		nextState = fsm[state][event].nextState;

		assert(nextState >= OFF && nextState <= GOINGDNTO2);

		if (on_entry[nextState])
		{
			assert(on_entry[nextState]);
			(on_entry[nextState])();
		}
	}

	INFO_PRINT("current state = %s", elevatorStateEnumNames(state));
	INFO_PRINT("new state = %s\n", elevatorStateEnumNames(nextState));
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
	// this is where timers are handled
	DEBUG_PRINT("controller tick\n");
}

void controller_init() // also the power on event
{
	printf("%s\n", __FUNCTION__);

	currentState = FLOOR2;
	// clear all timers
}

void off_state_entry()
{
	printf("%s\n", __FUNCTION__);
	int eCmd = ALL_OFF;
	elevator_control_cmd(eCmd);
}

void floor2_state_entry()
{
	printf("%s\n", __FUNCTION__);
	int eCmd = ALL_OFF;
	elevator_control_cmd(eCmd);
}

void floor3_state_entry()
{
	printf("%s\n", __FUNCTION__);
	int eCmd = ALL_OFF;
	elevator_control_cmd(eCmd);
}

void floor4_state_entry()
{
	printf("%s\n", __FUNCTION__);
	int eCmd = ALL_OFF;
	elevator_control_cmd(eCmd);
}

void goingdnto2_state_entry()
{
	printf("%s\n", __FUNCTION__);
	int eCmd = GO_DOWN;
	elevator_control_cmd(eCmd);
}

void goingdnto3_state_entry()
{
	printf("%s\n", __FUNCTION__);
	int eCmd = GO_DOWN;
	elevator_control_cmd(eCmd);
}

void goingupto3_state_entry()
{
	printf("%s\n", __FUNCTION__);
	int eCmd = GO_UP;
	elevator_control_cmd(eCmd);
}

void goingupto4_state_entry()
{
	printf("%s\n", __FUNCTION__);
	int eCmd = GO_UP;
	elevator_control_cmd(eCmd);
}

const char *elevatorStateEnumNames(elevatorStateEnum e)
{
	assert(e >= OFF && e <= GOINGDNTO2);

	const char *n[] = {"OFF",
					   "FLOOR2",
					   "FLOOR3",
					   "FLOOR4",
					   "GOINGUPTO3",
					   "GOINGDNTO3",
					   "GOINGUPTO4",
					   "GOINGDNTO2"};
	return n[e];
}
