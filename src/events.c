#include <assert.h>

#include "events.h"

const char *eventEnumName(eventEnum e)
{
    const char *n[] = {
        "TIMER_EXPIRED",
        "POWER_ON",
        "DOOR_IS_OPEN",
        "DOOR_IS_CLOSED",
        "DOOR_IS_OBSTRUCTED",
        "CAB_POSITION_FLOOR_2",
        "CAB_POSITION_FLOOR_2_5",
        "CAB_POSITION_FLOOR_3",
        "CAB_POSITION_FLOOR_3_5",
        "CAB_POSITION_FLOOR_4",
        "CALL_FLOOR_2",
        "CALL_FLOOR_3",
        "CALL_FLOOR_4",
        "REQ_DOOR_OPEN",
        "REQ_STOP",
        "REQ_FLOOR_2",
        "REQ_FLOOR_3",
        "REQ_FLOOR_4",
        "REQ_BELL_PRESSED",
        "REQ_BELL_RELEASED"};

    assert(e >= POWER_ON && e <= REQ_BELL_RELEASED);
    return n[e];
}
