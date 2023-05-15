#include "time_mission.h"

TimeMission::TimeMission(
        int _mission_id,
        LLInt _start_timestamp,
        LLInt _end_timestamp,
        int _target_time_in_minutes,
        int _reward_amount)
        : Mission(_mission_id, _start_timestamp, _end_timestamp, _reward_amount)
        {
            if (_target_time_in_minutes  <0)
                throw InvalidArgument();

            target_time_in_minutes = _target_time_in_minutes;
        }
