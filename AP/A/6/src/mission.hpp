#pragma once
#include "timestamp.hpp"
#include "ride.hpp"
#include <iostream>
using namespace std;

class Mission
{
public:
    Mission(int _mission_id, LLInt _start_timestamp, LLInt _end_timestamp, int _reward_amount);
    Timestamp get_timestamp() { return timestamp; }
    int get_mission_id() { return mission_id; }
    bool get_completed() { return completed; }
    virtual void add_ride_info(shared_ptr<Ride> ride){};
    bool within_mission(Timestamp timestamp);
    void show_status();
    void show_completed_mission_status();
    virtual shared_ptr<Mission> clone() const = 0;

protected:
    Mission();

    int mission_id;
    Timestamp timestamp;
    int reward_amount;
    bool completed = false;
};