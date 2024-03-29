#pragma once
#include "mission.hpp"

class TimeMission : public Mission
{
public:
    TimeMission(
        int _mission_id,
        LLInt _start_timestamp,
        LLInt _end_timestamp,
        int _target_time_in_minutes,
        int _reward_amount);
    virtual void add_ride_info(shared_ptr<Ride> ride) override;
    shared_ptr<Mission> clone() const override;

private:
    int target_time_in_minutes;
    LLInt total_ride_time;
};