#include "events.h"
#include "elevator.h"

// https://github.com/imb/fctx/tree/master

#include "fct.h"
#include <string.h>

FCT_BGN()
{

   FCT_SUITE_BGN(misc things)
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
   }
   FCT_SUITE_END();

   FCT_SUITE_BGN(door)
   {
      FCT_TEST_BGN(open)
      {
         printf("\n");

         // initialize the elevator
         init_elevator();

         // turn it on
         power_on();

         // the door should be closed
         fct_chk(door_position() == 5); // 5 is closed */

         // send the command to open the door
         elevator_control_cmd(OPEN_DOOR);
         // tick() it
         for (int i = 0; i < 5; i++) // 5 seconds
         {
            elevator_tick();
            printf("the door pos is %d\n", door_position());
         }
         // test if it is open
         fct_chk(door_position() == 0);
         printf("\n");
      }
      FCT_TEST_END();

      FCT_TEST_BGN(close)
      {
         printf("\n");

         // initialize the elevator
         init_elevator();

         // turn it on
         power_on();

         // the door should be closed
         fct_chk(door_position() == 5); // 5 is closed */

         // send the command to open the door
         elevator_control_cmd(OPEN_DOOR);

         // tick() it
         for (int i = 0; i < 5; i++) // 5 seconds
         {
            elevator_tick();
            printf("the door pos is %d\n", door_position());
         }
         // test if it is open
         fct_chk(door_position() == 0);

         // Now close it
 
         // send the command to close the door
         elevator_control_cmd(CLOSE_DOOR);

         // tick() it
         for (int i = 0; i < 5; i++) // 5 seconds
         {
            elevator_tick();
            printf("the door pos is %d\n", door_position());
         }
         // test if it is closed
         fct_chk(door_position() == 5);
         printf("\n");
      }
      FCT_TEST_END();
   }
   FCT_SUITE_END();

   FCT_END();
}
