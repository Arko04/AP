#include "mission.h"

class CountMission : public Mission
{
public:
    CountMission(
        int _mission_id,
        LLInt _start_timestamp,
        LLInt _end_timestamp,
        int _target_number,
        int _reward_amount);

private:
    int target_number;
    int total_ride_number = 0;
};