#include "mission.hpp"

class DistanceMission : public Mission
{
public:
    DistanceMission(
        int _mission_id,
        LLInt _start_timestamp,
        LLInt _end_timestamp,
        int _target_distance_in_meters,
        int _reward_amount);
    virtual void add_ride_info(shared_ptr<Ride> ride) override;
    shared_ptr<Mission> clone() const override;

private:
    int target_distance_in_meters;
    int total_ride_distance;
};