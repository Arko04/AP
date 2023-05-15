#pragma once
#include "mission.h"
class TimeMission : public Mission
{
    public:
    TimeMission(
        int _mission_id,
        LLInt _start_timestamp,
        LLInt _end_timestamp,
        int _target_time_in_minutes,
        int _reward_amount);

    private:
    int target_time_in_minutes;
    int total_ride_time = 0;
};