#include <iostream>
#include "mission.hpp"
#include "const.hpp"
#include <stdexcept>

Mission::Mission(int _mission_id, LLInt _start_timestamp, LLInt _end_timestamp, int _reward_amount)
    : timestamp(_start_timestamp, _end_timestamp)
{
    if (_reward_amount < 0)
        throw invalid_argument(EMPTY);
    mission_id = _mission_id;
    reward_amount = _reward_amount;
}

// Mission::Mission(const shared_ptr<Mission> mission) : timestamp(0, 0)
// {
//     Timestamp _timestamp = mission->timestamp;
//     this->timestamp = _timestamp;
//     int _mission_id = mission->mission_id;
//     this->mission_id = _mission_id;
//     int _reward_amount = mission->reward_amount;
//     this->reward_amount =mission->reward_amount;
//     bool _completed = false;
//     this->completed = _completed;
// }
// Mission &Mission::operator=(const Mission &mission)
// {
//     this->timestamp = mission.timestamp;
//     this->mission_id = mission.mission_id;
//     this->reward_amount = mission.reward_amount;
//     this->completed = false;
//     return *this;
// }
Mission::Mission() : timestamp(0, 0)
{
} 

// void Mission::set_mission(const shared_ptr<Mission> mission)
// {
//     this->completed = false;
//     this->mission_id = mission->mission_id;
//     this->timestamp = mission->timestamp;
//     this->reward_amount = mission->reward_amount;
// }

bool Mission::within_mission(Timestamp _timestamp)
{
    return (this->timestamp.get_start_timestamp() <= _timestamp.get_start_timestamp() &&
            this->timestamp.get_end_timestamp() >= _timestamp.get_end_timestamp());
}

void Mission::show_status()
{
    cout << "mission " << mission_id << DATA_DELIMITER << endl
         << "start timestamp: " << timestamp.get_start_timestamp() << endl
         << "end timestamp: " << ((completed) ? timestamp.get_end_timestamp() : -1) << endl
         << "reward: " << reward_amount << endl
         << "status: " << ((completed) ? "completed" : "ongoing")
         << endl;
}

void Mission::show_completed_mission_status()
{
    cout << "mission: " << mission_id << endl
         << "start timestamp: " << timestamp.get_start_timestamp() << endl
         << "end timestamp: " << timestamp.get_end_timestamp() << endl
         << "reward: " << reward_amount 
         << endl;
}
