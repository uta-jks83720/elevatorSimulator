#include <assert.h>


#include "elevatorController.h"


#include "controls_to_elevator.h"
#include "events_from_elevator.h"
#include "indicators.h"
#include "user_events.h"


// This is an example elevator controller.  As part of the
// assignment, students are to re-implement the elevator controller
// to meet the requirements (state diagram) of a previous assignment.
//
//
// Specifics of this sample controller:
//       1.  On power on, the elevator goes to the bottom floor (floor 2), and opens the
//           doors.
//       2.  When a 'REQUEST' button is pressed, the elevator goes to that floor.
//       3.  When a 'CALL' button is pressed, the elevator goes to that floor.
//       4.  Once a CALL or a REQUEST is accepted, others are ignored until the elevator gets
//           to the desired floor.



// These functions are mandatory.  They must be implement with the same name and arguments
int some_function()
{
	return 0;
}

// The rest of these functions are not mandatory.  Students can implement the logic using 
// any design, however it must be using the C language.
//
void off_state_entry()
{
}

void floor2_state_entry()
{
}

void floor3_state_entry()
{
}

void floor4_state_entry()
{
}

void goingto2_state_entry()
{
}

void goingto3_state_entry()
{
}

void goingto4_state_entry()
{
}

typedef enum {OFF,FLOOR2,FLOOR3,FLOOR4,GOINGTO2,GOINGTO3,GOINGTO4} elevatorStateEnum;
static elevatorStateEnum currentState,nextState;


