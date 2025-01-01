#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    /* Elevator Controls are sent to the elevator in a single 32 bit word
       with the aproprtiate bits set.
       You must provide all of the controls, each time the command is sent.
    */

#define ALL_OFF 0x000000000
#define POWER_ON 0x00000001
#define GO_UP 0x00000002
#define GO_DOWN 0x00000004
#define STOP 0x00000008
#define OPEN_DOOR 0x00000010
#define CLOSE_DOOR 0x00000020

    int elevator_control_cmd(unsigned int);

#ifdef __cplusplus
}
#endif
