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
    // cout <<"xxxxxx\nn\\n\n\n\n\n";
    if (!within_mission(ride->get_timestamp()) || completed)
        {
            // cout <<"gavvv\n\n\n\n\\n\n";
            return;
        }
    // cout <<total_ride_time<<" missionID : "<<mission_id<<endl;
    total_ride_time += ride->get_timestamp().calc_time_gap_in_minute();
    if (total_ride_time >= target_time_in_minutes)
    {
        completed = true;
        timestamp.set_end_timestamp(ride->get_timestamp().get_end_timestamp());
    }
}

// TimeMission::TimeMission(const shared_ptr<TimeMission> time_mission) : Mission(time_mission)
// {
//     // Mission(time_mission);
//     // *this = time_mission;
//     // this->timestamp = time_mission->timestamp;
//     // this->mission_id = time_mission->mission_id;
//     // this->reward_amount = time_mission->reward_amount;
//     // this->completed = false;
//     target_time_in_minutes = time_mission->target_time_in_minutes;
//     total_ride_time = 0;
// }

// void TimeMission::set_mission(const shared_ptr<TimeMission> time_mission)
// {
//     Mission::set_mission(time_mission);
//     target_time_in_minutes = time_mission->target_time_in_minutes;
//     total_ride_time = 0;
// }