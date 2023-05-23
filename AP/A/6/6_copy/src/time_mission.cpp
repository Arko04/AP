#include "time_mission.hpp"

TimeMission::TimeMission(
    int _mission_id,
    LLInt _start_timestamp,
    LLInt _end_timestamp,
    int _target_time_in_minutes,
    int _reward_amount)
    : Mission(_mission_id, _start_timestamp, _end_timestamp, _reward_amount)
{
    if (_target_time_in_minutes < 0)
        throw invalid_argument("");

    target_time_in_minutes = _target_time_in_minutes;
}
void TimeMission::add_ride_info(Ride ride)
{
    if (!within_mission(ride.get_timestamp()) || completed)
        return;
    total_ride_time += ride.get_timestamp().calc_time_gap_in_minute();
    if (total_ride_time >= target_time_in_minutes)
    {
        completed = true;
        timestamp.set_end_timestamp(ride.get_timestamp().get_end_timestamp());
    }
}