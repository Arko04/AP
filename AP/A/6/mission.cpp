
#include "mission.h"

Mission::Mission(int _mission_id, LLInt _start_timestamp, LLInt _end_timestamp, int _reward_amount)
:timestamp(_start_timestamp, _end_timestamp)
{
    if (_reward_amount < 0)
        throw InvalidArgument();
    mission_id = _mission_id;
    reward_amount = _reward_amount;
}
