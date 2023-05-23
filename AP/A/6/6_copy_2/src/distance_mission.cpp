#include "distance_mission.hpp"
#include "const.hpp"
#include <stdexcept>

DistanceMission::DistanceMission(
    int _mission_id,
    LLInt _start_timestamp,
    LLInt _end_timestamp,
    int _target_distance_in_meters,
    int _reward_amount)
    : Mission(_mission_id, _start_timestamp, _end_timestamp, _reward_amount)

{
    if (_target_distance_in_meters < 0)
        throw invalid_argument(EMPTY);

    target_distance_in_meters = _target_distance_in_meters;
    total_ride_distance = 0;
}

void DistanceMission::add_ride_info(shared_ptr<Ride> ride)
{
    if (!within_mission(ride->get_timestamp()) || completed)
        return;
    total_ride_distance += ride->get_distance();
    // cout <<total_ride_distance<<" missionID : "<<mission_id<<endl;
    if (total_ride_distance >= target_distance_in_meters)
    {
        completed = true;
        timestamp.set_end_timestamp(ride->get_timestamp().get_end_timestamp());
    }
}

// DistanceMission::DistanceMission(const shared_ptr<DistanceMission> distance_mission) : Mission(distance_mission)
// {
//     // Mission(distance_mission);
//     // *this = distance_mission;
//     // this->timestamp = distance_mission->timestamp;
//     // this->mission_id = distance_mission->mission_id;
//     // this->reward_amount = distance_mission->reward_amount;
//     // this->completed = false; 
//     target_distance_in_meters = distance_mission->target_distance_in_meters;
//     total_ride_distance = 0;
// }

// void DistanceMission::set_mission(const shared_ptr<DistanceMission> distance_mission)
//  {
//     Mission::set_mission(distance_mission);
//     target_distance_in_meters = distance_mission->target_distance_in_meters;
//     total_ride_distance = 0;
//  }