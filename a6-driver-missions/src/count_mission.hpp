#include "mission.hpp"

class CountMission : public Mission
{
public:
    CountMission(
        int _mission_id,
        LLInt _start_timestamp,
        LLInt _end_timestamp,
        int _target_number,
        int _reward_amount);
    virtual void add_ride_info(shared_ptr<Ride> ride) override;
    shared_ptr<Mission> clone() const override;

private:
    int target_number;
    int total_ride_number;
};