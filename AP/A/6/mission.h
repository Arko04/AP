#pragma once
#include "timestamp.h"
#include "ride.h"
class Mission{
public:
Mission(int _mission_id, LLInt _start_timestamp, LLInt _end_timestamp, int _reward_amount);
int get_mission_id(){ return mission_id;}
bool get_completed(){ return completed;}
virtual void add_ride_info(Ride ride){} // = 0 ???
protected:
    int mission_id;
    Timestamp timestamp;
    int reward_amount;
    bool completed = false;
};