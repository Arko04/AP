#include <sstream>
#include <fstream>
#include "TeamManager.hpp"
#include "Const.hpp"

vector<shared_ptr<RealTeam>> TeamManager::get_real_teams() { return real_teams; }

TeamManager::TeamManager(const string &directory)
{
    vector<TeamInfo> teams_info;
    string filename = directory + ADDR_DELIMITER + PREMIER_LEAGUE_FILE;
    ifstream input_team_file(filename);
    if (!input_team_file)
        cout << FILE_NOT_FOUND << endl;
    string line;
    getline(input_team_file, line);

    while (getline(input_team_file, line))
    {
        TeamInfo team_info = parse_team_info(line);
        teams_info.push_back(team_info);
    }
    set_teams_info(teams_info);
}

vector<string> TeamManager::split_by(const char &delimiter, string &line)
{
    stringstream input(line);
    string token;
    vector<string> tokens;

    while (getline(input, token, delimiter))
        tokens.push_back(token);

    return tokens;
}

TeamInfo TeamManager::parse_team_info(string line)
{
    TeamInfo team_info;
    vector<string> fields = split_by(TOKEN_DELIMITER, line);
    string team_name = fields[0];
    team_info.team_name = team_name;

    string goalkeepers = fields[1];
    team_info.goalkeepers = split_by(PLAYERS_DELIMITER, goalkeepers);

    string defenders = fields[2];
    team_info.defenders = split_by(PLAYERS_DELIMITER, defenders);

    string midfielders = fields[3];
    team_info.midfielders = split_by(PLAYERS_DELIMITER, midfielders);

    string forwards = fields[4];
    team_info.forwards = split_by(PLAYERS_DELIMITER, forwards);

    return team_info;
}

void TeamManager::set_teams_info(vector<TeamInfo> teams_info)
{
    for (TeamInfo team_info : teams_info)
    {
        shared_ptr<RealTeam> real_team = make_shared<RealTeam>(team_info);
        real_teams.push_back(real_team);
    }
}