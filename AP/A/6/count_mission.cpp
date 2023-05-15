
#include "count_mission.h"

CountMission::CountMission(
    int _mission_id,
    LLInt _start_timestamp,
    LLInt _end_timestamp,
    int _target_number,
    int _reward_amount)
    : Mission(_mission_id, _start_timestamp, _end_timestamp, _reward_amount)
{
    if (_target_number < 0)
        throw InvalidArgument();

    target_number = _target_number;
}
