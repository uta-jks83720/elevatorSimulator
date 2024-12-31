#ifdef __cplusplus
extern "C" {
#endif

typedef enum {DOOR_IS_OPEN,DOOR_IS_CLOSED,DOOR_IS_OBSTRUCTED,CAB_POSITION_FLOOR_2,CAB_POSITION_FLOOR_2_5,CAB_POSITION_FLOOR_3,CAB_POSITION_FLOOR_3_5,CAB_POSITION_FLOOR_4} elevatorEventEnum;


void event_to_controller(elevatorEventEnum e);

#ifdef __cplusplus
}
#endif
