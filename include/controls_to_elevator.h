#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {POWER_ON,GO_UP,GO_DOWN,STOP,OPEN_DOOR,CLOSE_DOOR} ElevatorControlsEnum;
const char* ElevatorControlsEnumName(ElevatorControlsEnum e);
void elevator_control(ElevatorControlsEnum e,int on);

#ifdef __cplusplus
}
#endif
