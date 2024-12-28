#pragma once

// The physical elevator is simulated here.

#ifdef __cplusplus
extern "C" 
{
#endif

    // this function is called once a second by FLTK.
void tick();
    // this function is called when the simulated power is turned off
void init_elevator();
    // this function returns the time in seconds
unsigned int timeInSeconds();

void power_on();

void power_off();

#ifdef __cplusplus
}
#endif
