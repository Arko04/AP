#pragma once
#include "time_mission.hpp"
#include "distance_mission.hpp"
#include "count_mission.hpp"
#include "driver.hpp"
#include <iostream>
#include <vector>

class Manager
{
public:
    void handle_adding_time_mission(vector<string> command_fields);
    void handle_adding_distance_mission(vector<string> command_fields);
    void handle_adding_count_mission(vector<string> command_fields);
    void handle_assigning_mission(vector<string> command_fields);
    void handle_recording_ride(vector<string> command_fields);
    void handle_showing_missions_status(vector<string> command_fields);

private:
    void add_time_mission(vector<string> command_fields);
    void add_distance_mission(vector<string> command_fields);
    void add_count_mission(vector<string> command_fields);
    void assign_mission(vector<string> command_fields);
    void record_ride(vector<string> command_fields);
    void show_missions_status(vector <string> command_fields);

    shared_ptr <Mission> find_mission(int mission_id);
    shared_ptr <Driver> find_driver(int driver_id);

    bool added(int mission_id);

private:
    vector<shared_ptr<Mission>  > missions;
    vector<shared_ptr<Driver> > drivers;
};

// void init_count_mission(
//     const vector <string>& command_fields,
//     int &_mission_id,
//     LLInt &_start_timestamp,
//     LLInt &_end_timestamp,
//     int &_target_number,
//     int &_reward_amount);

// void init_mission(
//     const vector <string>& command_fields,
//     int &_mission_id,
//     LLInt &_start_timestamp,
//     LLInt &_end_timestamp,
//     int &_reward_amount);

// void init_timestamp(
//     const vector <string>& command_fields,
//     LLInt &_start_timestamp,
//     LLInt &_end_timestamp);