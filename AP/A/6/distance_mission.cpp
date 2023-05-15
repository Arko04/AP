
#include "distance_mission.h"

DistanceMission::DistanceMission(
    int _mission_id,
    LLInt _start_timestamp,
    LLInt _end_timestamp,
    int _target_distance_in_meters,
    int _reward_amount)
    : Mission(_mission_id, _start_timestamp, _end_timestamp, _reward_amount)

{
    if (_target_distance_in_meters < 0)
        throw InvalidArgument();

    target_distance_in_meters = _target_distance_in_meters;
    
}
