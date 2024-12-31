#include "elevatorController.h"
//#include "controls_to_elevator.h"
//#include "events_from_elevator.h"



// https://github.com/imb/fctx/tree/master
#include "fct.h"
#include <string.h>



FCT_BGN()
{
   /* A simple test case. No setup/teardown. */
   FCT_SUITE_BGN(simple)
   {
      /* An actual test case in the test suite. */
        //char *names[]= {"OFF","FLOOR2","FLOOR3","FLOOR4","GOINGUPTO3","GOINGDNTO3","GOINGUPTO4","GOINGDNTO2"};
      FCT_TEST_BGN(fsm transition)
      {
          printf("\n");
          //controller_init();
          //printf(" state is %s \n",controller_current_state());
          //elevatorStateEnum transition(elevatorStateEnum state, elevatorEventEnum event)
          //typedef enum {DOOR_IS_OPEN,DOOR_IS_CLOSED,DOOR_IS_OBSTRUCTED,CAB_POSITION_FLOOR_2,CAB_POSITION_FLOOR_2_5,CAB_POSITION_FLOOR_3,CAB_POSITION_FLOOR_3_5,CAB_POSITION_FLOOR_4} elevatorEventEnum;
          //printf(" new state is %s\n",ENUM_TO_STRING(transition(OFF,DOOR_IS_OPEN)));
          //printf(" new state is %s\n",elevatorStateEnumNames(transition(OFF,DOOR_IS_CLOSED)));
          //printf(" new state is %s\n",elevatorStateEnumNames(transition(FLOOR2,DOOR_IS_OPEN)));
          //printf(" new state is %s\n",elevatorStateEnumNames(transition(FLOOR2,DOOR_IS_CLOSED)));
          //fct_chk( transition(OFF,DOOR_IS_OPEN) == (stateEnum) DOOR_IS_OPEN);
          printf("\n");
      }
      FCT_TEST_END();

      FCT_TEST_BGN(chk_neq)
      {
         fct_chk(strcmp("daka", "durka") !=0 );
      }
      FCT_TEST_END();


   /* Every test suite must be closed. */
   }
   FCT_SUITE_END();

/* Every FCT scope has an end. */
}
FCT_END();

