#include "time_mission.hpp"
#include "const.hpp"
#include <stdexcept>

TimeMission::TimeMission(
    int _mission_id,
    LLInt _start_timestamp,
    LLInt _end_timestamp,
    int _target_time_in_minutes,
    int _reward_amount)
    : Mission(_mission_id, _start_timestamp, _end_timestamp, _reward_amount)
{
    if (_target_time_in_minutes < 0)
        throw invalid_argument(EMPTY);

    target_time_in_minutes = _target_time_in_minutes;
    total_ride_time = 0;
}

void TimeMission::add_ride_info(shared_ptr<Ride> ride)
{
    if (!within_mission(ride->get_timestamp()) || completed)
        return;

    total_ride_time += ride->get_timestamp().calc_time_gap_in_minute();
    if (total_ride_time >= target_time_in_minutes)
    {
        completed = true;
        timestamp.set_end_timestamp(ride->get_timestamp().get_end_timestamp());
    }
}

shared_ptr<Mission> TimeMission::clone() const
{
    return make_shared<TimeMission>(*this);
}