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
         fct_chk(elevator_control_cmd(GO_UP | GO_DOWN |STOP) == -1);
         fct_chk(elevator_control_cmd(GO_UP | STOP) == -1);
         fct_chk(elevator_control_cmd(STOP | GO_DOWN) == -1);

         printf("\n");
      }
      FCT_TEST_END();

      /* Every test suite must be closed. */
   }
   FCT_SUITE_END();

   /* Every FCT scope has an end. */
}
FCT_END();
