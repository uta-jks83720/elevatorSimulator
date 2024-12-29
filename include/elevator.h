#pragma once

// The physical elevator is simulated here.

#ifdef __cplusplus
extern "C" {
#endif

// called once a second by FLTK.
void elevator_tick();

// called when the simulated power is turned off
void init_elevator();

// returns the time in seconds
unsigned int timeInSeconds();

void power_on();

void power_off();

int power_status();

int cab_position();


#ifdef __cplusplus
}
#endif
