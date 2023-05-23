#include "distance_mission.hpp"

DistanceMission::DistanceMission(
    int _mission_id,
    LLInt _start_timestamp,
    LLInt _end_timestamp,
    int _target_distance_in_meters,
    int _reward_amount)
    : Mission(_mission_id, _start_timestamp, _end_timestamp, _reward_amount)

{
    if (_target_distance_in_meters < 0)
        throw invalid_argument("");

    target_distance_in_meters = _target_distance_in_meters;
    
}
 void DistanceMission::add_ride_info(Ride ride)
 {
    if(! within_mission(ride.get_timestamp()) || completed)
        return;
    total_ride_distance += ride.get_distance();
    if(total_ride_distance >= target_distance_in_meters)
        {completed = true;
        timestamp.set_end_timestamp(ride.get_timestamp().get_end_timestamp());
        }
 }
