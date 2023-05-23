#include "count_mission.hpp"
#include "const.hpp"
#include <stdexcept>

CountMission::CountMission(
    int _mission_id,
    LLInt _start_timestamp,
    LLInt _end_timestamp,
    int _target_number,
    int _reward_amount)
    : Mission(_mission_id, _start_timestamp, _end_timestamp, _reward_amount)
{
    if (_target_number < 0)
        throw invalid_argument(EMPTY);

    target_number = _target_number;
    total_ride_number = 0;
}

void CountMission::add_ride_info(shared_ptr<Ride> ride)
{
    if (!within_mission(ride->get_timestamp()) || completed)
        return;
    total_ride_number += 1;
    // cout <<total_ride_number<<" missionID : "<<mission_id<<endl;
    if (total_ride_number >= target_number)
    {
        completed = true;
        timestamp.set_end_timestamp(ride->get_timestamp().get_end_timestamp());
    }
}

// CountMission::CountMission(const shared_ptr<CountMission> count_mission) : Mission(count_mission)
// {   
//     // *this = count_mission;

//     // this->timestamp = count_mission->timestamp;
//     // this->mission_id = count_mission->mission_id;
//     // this->reward_amount = count_mission->reward_amount;
//     // this->completed = false;
//     target_number = count_mission->target_number;
//     total_ride_number = 0;
// }

//   void CountMission::set_mission(const shared_ptr<CountMission> count_mission)
//  {
//     Mission::set_mission(count_mission);
//     target_number = count_mission->target_number;
//     total_ride_number = 0;

//  }