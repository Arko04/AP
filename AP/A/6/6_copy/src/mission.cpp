
#include "mission.hpp"

Mission::Mission(int _mission_id, LLInt _start_timestamp, LLInt _end_timestamp, int _reward_amount)
    : timestamp(_start_timestamp, _end_timestamp)
{
    if (_reward_amount < 0)
        throw invalid_argument("");
    mission_id = _mission_id;
    reward_amount = _reward_amount;
}

Mission::Mission(const Mission &mission) : timestamp(0, 0)
{
    this->timestamp = mission.timestamp;
    this->mission_id = mission.mission_id;
    this->reward_amount = mission.reward_amount;
}
Mission &Mission::operator=(const Mission &mission)
{
    this->timestamp = mission.timestamp;
    this->mission_id = mission.mission_id;
    this->reward_amount = mission.reward_amount;
    return *this;
}
bool Mission::within_mission(Timestamp _timestamp)
{
    return (this->timestamp.get_start_timestamp() <= _timestamp.get_start_timestamp() &&
            this->timestamp.get_end_timestamp() >= _timestamp.get_end_timestamp());
}
void Mission::show_status()
{
    cout << "mission " << mission_id << ":" << endl
         << "start timestamp: " << timestamp.get_start_timestamp() << endl
         << "end timestamp: " << ((completed) ? timestamp.get_end_timestamp() : -1) << endl
         << "reward: " << reward_amount << endl
         << "status: " << ((completed) ? "completed" : "ongoing") << '\n'
         << endl;
}
// void Mission::add_ride_info(Ride ride){

// }

void Mission::show_completed_mission_status()
{
    cout << "mission " << mission_id << ":" << endl
         << "start timestamp: " << timestamp.get_start_timestamp() << endl
         << "end timestamp: " << timestamp.get_end_timestamp() << endl
         << "reward: " << reward_amount << '\n'
         << endl;
}
