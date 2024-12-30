// https://github.com/imb/fctx/tree/master
#include "fct.h"
#include <string.h>

FCT_BGN()
{
   /* A simple test case. No setup/teardown. */
   FCT_SUITE_BGN(simple)
   {
      /* An actual test case in the test suite. */
      FCT_TEST_BGN(strcmp_eq)
      {
         fct_chk(strcmp("durka", "durka") == 0);
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
