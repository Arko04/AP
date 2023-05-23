#include "count_mission.hpp"

CountMission::CountMission(
    int _mission_id,
    LLInt _start_timestamp,
    LLInt _end_timestamp,
    int _target_number,
    int _reward_amount)
    : Mission(_mission_id, _start_timestamp, _end_timestamp, _reward_amount)
{
    if (_target_number < 0)
        throw invalid_argument("");

    target_number = _target_number;
}
void CountMission::add_ride_info(Ride ride)
{
    if (!within_mission(ride.get_timestamp()) || completed)
        return;
    total_ride_number += 1;
    if (total_ride_number >= target_number)
        {completed = true;
        timestamp.set_end_timestamp(ride.get_timestamp().get_end_timestamp());
        }
}