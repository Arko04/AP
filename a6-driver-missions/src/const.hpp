#pragma once
#include <string>
using namespace std;

const int COMMAND = 0;

const char DATA_DELIMITER = ':';
const char SPACE = ' ';

const string ADD_TIME_MISSION = "add_time_mission";
const string ADD_COUNT_MISSION = "add_count_mission";
const string ADD_DISTANCE_MISSION = "add_distance_mission";
const string ASSIGN_MISSION = "assign_mission";
const string RECORD_RIDE = "record_ride";
const string SHOW_MISSIONS_STATUS = "show_missions_status";
const string EMPTY = "";

const string OK = "OK";
const string INVALID_ARGUMENTS = "INVALID_ARGUMENTS";
const string DUPLICATE_MISSION_ID = "DUPLICATE_MISSION_ID";
const string MISSION_NOT_FOUND = "MISSION_NOT_FOUND";
const string DUPLICATE_DRIVER_MISSION = "DUPLICATE_DRIVER_MISSION";
const string DRIVER_MISSION_NOT_FOUND = "DRIVER_MISSION_NOT_FOUND";
