#include "WeekManager.hpp"
#include "Const.hpp"
#include "Utils.hpp"
#include <fstream>
#include <sstream>

WeekManager::WeekManager(const string &_filename)
{
    week_index = 0;
    filename = _filename;
}

shared_ptr<Week> WeekManager::pass_week()
{
    vector<shared_ptr<MatchInfo>> matches_info;

    ++week_index;
    string curr_week_file = filename + ADDR_DELIMITER + WEEK + to_string(week_index) + CSV_EXTENTION;
    ifstream input_week_file(curr_week_file);

    string line;
    getline(input_week_file, line);

    while (getline(input_week_file, line))
    {
        shared_ptr<MatchInfo> match_info = parse_match_info(line);
        matches_info.push_back(match_info);
    }
    shared_ptr<Week> week = make_shared<Week>(matches_info);
    return week;
}

vector<vector<string>> WeekManager::get_scores(string field)
{
    vector<string> tokens = Utils::split_by(PLAYERS_DELIMITER, field);
    vector<vector<string>> scores;
    for (string token : tokens)
    {
        vector<string> score = Utils::split_by(MATCH_DELIMITER, token);
        scores.push_back(score);
    }
    return scores;
}

shared_ptr<MatchInfo> WeekManager::parse_match_info(string line)
{
    shared_ptr<MatchInfo> match_info = make_shared<MatchInfo>();
    vector<string> fields = Utils::split_by(TOKEN_DELIMITER, line);
    Utils::remove_backslash_r(fields[7]);
    match_info->teams = Utils::split_by(MATCH_DELIMITER, fields[0]);
    match_info->team_goals = Utils::split_by(MATCH_DELIMITER, fields[1]);
    match_info->injured = Utils::split_by(PLAYERS_DELIMITER, fields[2]);
    match_info->yellow_card = Utils::split_by(PLAYERS_DELIMITER, fields[3]);
    match_info->red_card = Utils::split_by(PLAYERS_DELIMITER, fields[4]);

    vector<string> goal_with_assist_info = Utils::split_by(PLAYERS_DELIMITER, fields[5]);
    vector<vector<string>> goals_with_assists;
    for (string goal_with_assist : goal_with_assist_info)
        goals_with_assists.push_back(Utils::split_by(MATCH_DELIMITER, goal_with_assist));

    match_info->goal_with_assist = goals_with_assists;
    match_info->team_players.push_back(Utils::split_by(PLAYERS_DELIMITER, fields[6]));
    match_info->team_players.push_back(Utils::split_by(PLAYERS_DELIMITER, fields[7]));

    return match_info;
}