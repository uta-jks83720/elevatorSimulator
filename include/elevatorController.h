// This is the controller for the elevator.
// It is implemented strictly in the C programming language,
// but is callable by a C++ program, like for example an FLTK
// window, or a unit test framework
//
/////////////////////////////////////////////////////////////
#pragma once

#include <stdbool.h>

#include "events.h"

#ifdef __cplusplus
extern "C"
{
#endif

    // States of the elevator system

    typedef enum
        {
        OFF,
        INIT,
        FLOOR2,
        FLOOR3,
        FLOOR4,
        GOINGUPTO3,
        GOINGDNTO3,
        GOINGUPTO4,
        GOINGDNTO2,
        // New states from state diagram
        FLOOR2_DOOR_OPENING,
        FLOOR2_DOOR_OPEN,
        FLOOR2_DOOR_CLOSING,
        FLOOR2_DOOR_CLOSED,
        FLOOR3_DOOR_OPENING,
        FLOOR3_DOOR_OPEN,
        FLOOR3_DOOR_CLOSING,
        FLOOR3_DOOR_CLOSED,
        FLOOR4_DOOR_OPENING,
        FLOOR4_DOOR_OPEN,
        FLOOR4_DOOR_CLOSING,
        FLOOR4_DOOR_CLOSED,
        MOVING_UP,
        MOVING_DOWN,
        CAB_POS_2_5,
        CAB_POS_3_5
    } elevatorStateEnum;

    void controller_tick();
    void controller_init();

    const char *elevatorStateEnumNames(elevatorStateEnum e);

    // visibility to support testing
    elevatorStateEnum transition(elevatorStateEnum state, eventEnum event);
#ifdef __cplusplus
}
#endif
