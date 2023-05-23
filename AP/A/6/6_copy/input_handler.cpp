#include "input_handler.hpp"
#include <sstream>

vector<string> InputHandler::split(string line)
{
    stringstream input(line);
    string word;
    vector<string> command_fields;

    while (getline(input, word, ' '))
        command_fields.push_back(word);

    return command_fields;
}

void InputHandler::handle_command(vector<string> &command_fields)
{
    if (command_fields.empty())
        return;
    string command = command_fields[0];
    command_fields.erase(command_fields.begin());

   
    if (command == "add_time_mission")
        manager.handle_adding_time_mission(command_fields);
    else if (command == "add_distance_mission")
        manager.handle_adding_distance_mission(command_fields);
    else if (command == "add_count_mission")
        manager.handle_adding_count_mission(command_fields);
    else if (command == "assign_mission")
        manager.handle_assigning_mission(command_fields);
    else if (command == "record_ride")
        manager.handle_recording_ride(command_fields);
    else if (command == "show_missions_status")
        manager.handle_showing_missions_status(command_fields);
    else
    {
    }
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
