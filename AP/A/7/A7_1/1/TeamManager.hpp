#ifndef _TEAM_MANAGER_
#define _TEAM_MANAGER_
#include "RealTeam.hpp"
#include <memory>
#include <iostream>
using namespace std;

class TeamManager
{
private:
    vector<shared_ptr<RealTeam>> real_teams;

    void set_teams_info(vector<TeamInfo> teams_info);
    TeamInfo parse_team_info(string line);

public:
    TeamManager(const string &filename);
    vector<string> split_by(const char &delimiter, string &line);
    vector<shared_ptr<RealTeam>> get_real_teams();
};
#endif