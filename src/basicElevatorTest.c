#include "events.h"
#include "elevator.h"

// https://github.com/imb/fctx/tree/master

#include "fct.h"
#include <string.h>

FCT_BGN()
{

   FCT_SUITE_BGN(elevator unit tests)
   {

      FCT_TEST_BGN(invalid controls)
      {
         printf("\n");
         /*
            detect and ignore commands that do
            not make sense.
         */
         fct_chk(elevator_control_cmd(GO_UP | GO_DOWN) == -1);
         fct_chk(elevator_control_cmd(GO_UP | GO_DOWN | STOP) == -1);
         fct_chk(elevator_control_cmd(GO_UP | STOP) == -1);
         fct_chk(elevator_control_cmd(STOP | GO_DOWN) == -1);

         printf("\n");
      }
      FCT_TEST_END();

      FCT_TEST_BGN(door open operation)
      {
         printf("\n");
         /*
            detect and ignore commands that do
            not make sense.
         */
         printf("This test covers the operation of the door\n");

         // initialize the elevator
         init_elevator();

         // turn it on
         power_on();

         // the door should be closed
         fct_chk(door_position() == 5); // 5 is closed */

         // send the command to open the door
         elevator_control_cmd(OPEN_DOOR);
         // tick() it
         for (int i = 0; i < 6; i++) // 5 seconds
         {
            elevator_tick();
            printf("the door pos is %d\n", door_position());
         }
         // test if it is open
         fct_chk(door_position() == 0);
         printf("\n");
      }
      FCT_TEST_END();
      FCT_TEST_BGN(door open operation)
      {
         printf("\n");
         /*
            detect and ignore commands that do
            not make sense.
         */
         printf("This test covers the operation of the door\n");

         // initialize the elevator
         init_elevator();

         // turn it on
         power_on();

         // the door should be closed
         fct_chk(door_position() == 5); // 5 is closed */

         // send the command to open the door
         elevator_control_cmd(OPEN_DOOR);
         // tick() it
         for (int i = 0; i < 6; i++) // 5 seconds
         {
            elevator_tick();
            printf("the door pos is %d\n", door_position());
         }
         // test if it is open
         fct_chk(door_position() == 0);
         printf("\n");
      }
      FCT_TEST_END();

      /* Every test suite must be closed. */
   }
   FCT_SUITE_END();

   /* Every FCT scope has an end. */
}
FCT_END();
