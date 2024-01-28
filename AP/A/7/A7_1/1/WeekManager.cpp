#include <fstream>
#include <sstream>
#include "WeekManager.hpp"
#include "Const.hpp"

WeekManager::WeekManager(const string &_filename)
{
    week_index = 0;
    filename = _filename;
}

vector<string> WeekManager::split_by(const char &delimiter, string &line)
{
    stringstream input(line);
    string token;
    vector<string> tokens;

    while (getline(input, token, delimiter))
        tokens.push_back(token);

    return tokens;
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
    vector<string> tokens = split_by(PLAYERS_DELIMITER, field);
    vector<vector<string>> scores;
    for (string token : tokens)
    {
        vector<string> score = split_by(MATCH_DELIMITER, token);
        scores.push_back(score);
    }
    return scores;
}
shared_ptr<MatchInfo> WeekManager::parse_match_info(string line)
{
    shared_ptr<MatchInfo> match_info = make_shared<MatchInfo>();
    vector<string> fields = split_by(TOKEN_DELIMITER, line);
    match_info->teams = split_by(MATCH_DELIMITER, fields[0]);
    match_info->team_goals = split_by(MATCH_DELIMITER, fields[1]);
    match_info->injured = split_by(PLAYERS_DELIMITER, fields[2]);
    match_info->yellow_card = split_by(PLAYERS_DELIMITER, fields[3]);
    match_info->red_card = split_by(PLAYERS_DELIMITER, fields[4]);
    match_info->score = get_scores(fields[5]);
    return match_info;
}