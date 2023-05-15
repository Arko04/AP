#pragma once
#include "manager.h"
#include <vector>

class InputHandler{
public:
    void handle_input();
private:
 vector<string> split(string line);
 void handle_command(vector <string>& command_fields);
};