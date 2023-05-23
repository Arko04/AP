#pragma once
#include "manager.hpp"
#include <vector>

class InputHandler
{
public:
    void handle_input();

private:
    Manager manager;
    vector<string> split(string line);
    void handle_command(vector<string> &command_fields);
};