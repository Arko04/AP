#include "input_handler.hpp"
#include <sstream>
#include <iostream>
#include "const.hpp"

vector<string> InputHandler::split(string line)
{
    stringstream input(line);
    string word;
    vector<string> command_fields;

    while (getline(input, word, SPACE))
        command_fields.push_back(word);

    return command_fields;
}

void InputHandler::handle_command(vector<string> &command_fields)
{
    if (command_fields.size() < 2)
    {
        cout << INVALID_ARGUMENTS << endl;
        return;
    }

    string command = command_fields[COMMAND];
    command_fields.erase(command_fields.begin());

    if (command == ADD_TIME_MISSION)
        manager.handle_adding_time_mission(command_fields);
    else if (command == ADD_DISTANCE_MISSION)
        manager.handle_adding_distance_mission(command_fields);
    else if (command == ADD_COUNT_MISSION)
        manager.handle_adding_count_mission(command_fields);
    else if (command == ASSIGN_MISSION)
        manager.handle_assigning_mission(command_fields);
    else if (command == RECORD_RIDE)
        manager.handle_recording_ride(command_fields);
    else if (command == SHOW_MISSIONS_STATUS)
        manager.handle_showing_missions_status(command_fields);
    else {}
}

void InputHandler::handle_input()
{
    string command;
    vector<string> command_fields;

    while (getline(cin, command))
    {
        command_fields = split(command);
        handle_command(command_fields);
    }
}
