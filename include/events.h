#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        DOOR_IS_OPEN,
        DOOR_IS_CLOSED,
        DOOR_IS_OBSTRUCTED,
        CAB_POSITION_FLOOR_2,
        CAB_POSITION_FLOOR_2_5,
        CAB_POSITION_FLOOR_3,
        CAB_POSITION_FLOOR_3_5,
        CAB_POSITION_FLOOR_4,
        CALL_FLOOR_2,
        CALL_FLOOR_3,
        CALL_FLOOR_4,
        REQ_DOOR_OPEN,
        REQ_STOP,
        REQ_FLOOR_2,
        REQ_FLOOR_3,
        REQ_FLOOR_4,
        REQ_BELL_PRESSED,
        REQ_BELL_RELEASED
    } eventEnum;

    void event_to_controller(eventEnum e);

    const char *eventEnumName(eventEnum e);

#ifdef __cplusplus
}
#endif
