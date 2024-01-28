#include <sstream>
#include <fstream>
#include "TeamManager.hpp"
#include "Const.hpp"
#include "Utils.hpp"

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

void TeamManager::set_players_info(vector<pair<string, int>> &players, string field)
{
    string players_token = field;
    vector<string> players_info = Utils::split_by(PLAYERS_DELIMITER, players_token);
    for (string player_info : players_info)
    {
        vector<string> player = Utils::split_by(MATCH_DELIMITER, player_info);
        player[1].pop_back();
        players.push_back({player[0], stoi(player[1])});
    }
}

TeamInfo TeamManager::parse_team_info(string line)
{
    TeamInfo team_info;
    vector<string> fields = Utils::split_by(TOKEN_DELIMITER, line);

    Utils::remove_backslash_r(fields[4]);

    string team_name = fields[0];
    team_info.team_name = team_name;

    set_players_info(team_info.goalkeepers, fields[1]);
    set_players_info(team_info.defenders, fields[2]);
    set_players_info(team_info.midfielders, fields[3]);
    set_players_info(team_info.forwards, fields[4]);

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