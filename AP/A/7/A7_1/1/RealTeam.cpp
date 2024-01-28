#include "RealTeam.hpp"
#include "Const.hpp"
#include <algorithm>
#include <iomanip>

struct WantedPlayers
{
    string name;
    TeamPosition player_position;
    double score;
};

string RealTeam::get_team_name()
{
    return team_name;
}

void RealTeam::delete_last_character(shared_ptr<Player> player)
{
    player->set_player_name(player->remove_backslash_r(player->get_player_name()));
}

void RealTeam::add_player(vector<string> &players_info, void (RealTeam::*add_player)(shared_ptr<Player>), TeamPosition player_position)
{
    for (string player_info : players_info)
    {
        shared_ptr<Player> player = make_shared<Player>(player_info, player_position);
        (this->*add_player)(player);
        players.push_back(player);
    }
}

void RealTeam::add_goalkeeper(shared_ptr<Player> goalkeeper)
{
    goalkeepers.push_back(goalkeeper);
}

void RealTeam::add_defender(shared_ptr<Player> defender)
{
    defenders.push_back(defender);
}

void RealTeam::add_midfielder(shared_ptr<Player> midfielder)
{
    midfielders.push_back(midfielder);
}

void RealTeam::add_forward(shared_ptr<Player> forward)
{
    forwards.push_back(forward);
}

RealTeam::RealTeam(TeamInfo team_info)
{
    team_name = team_info.team_name;
    add_player(team_info.goalkeepers, &RealTeam::add_goalkeeper, GOALKEEPER);
    add_player(team_info.defenders, &RealTeam::add_defender, DEFENDER);
    add_player(team_info.midfielders, &RealTeam::add_midfielder, MIDFIELDER);
    add_player(team_info.forwards, &RealTeam::add_forward, FORWARD);

    delete_last_character(forwards.back());
    goals_for = 0;
    goals_against = 0;
    points = 0;
}

void RealTeam::add_players_score(vector<vector<string>> scores)
{
    for (shared_ptr<Player> player : players)
    {
        double score = get_player_score(player->get_player_name(), scores);
        if (score != DEFAULT_SCORE)
            player->add_attendent_game();
        player->set_player_score(score);
    }
}

double RealTeam::get_player_score(string player_name, vector<vector<string>> scores)
{
    for (vector<string> score : scores)
        if (player_name == score[PLAYER])
            return stod(score[SCORE]);

    return DEFAULT_SCORE;
}

void RealTeam::update_player_yellow_card(const vector<string> &player_names)
{
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = 0; j < player_names.size(); j++)
        {
            if (players[i]->get_player_name() == player_names[j])
            {
                players[i]->update_yellow_card();
            }
        }
    }
}

void RealTeam::update_player_red_card(const vector<string> &player_names)
{
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = 0; j < player_names.size(); j++)
        {
            if (players[i]->get_player_name() == player_names[j])
            {
                players[i]->update_red_card();
            }
        }
    }
}

void RealTeam::add_player_injury(const vector<string> &player_names)
{
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = 0; j < player_names.size(); j++)
        {
            if (player_names[j] == players[i]->get_player_name())
            {
                players[i]->set_player_off_week(OFF_WEEK_FOR_INJURY);
            }
        }
    }
}

void RealTeam::update_injured_players(const vector<string> &injured)
{
    add_player_injury(injured);
}

void RealTeam::update_team(shared_ptr<MatchInfo> match_info, int team_index)
{
    for (shared_ptr<Player> player : players)
    {
        player->check_player_availablity();
    }
    update_team_points(stoi(match_info->team_goals[team_index]), stoi(match_info->team_goals[1 - team_index]));
    add_players_score(match_info->score);
    update_injured_players(match_info->injured);
    update_player_yellow_card(match_info->yellow_card);
    update_player_red_card(match_info->red_card);
}

void RealTeam::update_team_points(const int &_goals_for, const int &_goals_against)
{
    goals_for += _goals_for;
    goals_against += _goals_against;

    if (_goals_for > _goals_against)
        points += 3;
    else if (_goals_for == _goals_against)
        points += 1;
}

bool comp_score(pair<string, double> score1, pair<string, double> score2)
{
    return score1.second > score2.second ||
           score1.second == score2.second && score1.first < score2.first;
}

bool comp_all_score(WantedPlayers score1, WantedPlayers score2)
{
    return score1.score > score2.score ||
           score1.score == score2.score && score1.name < score2.name;
}

void RealTeam::update_best_defenders(vector<pair<string, double>> &_defenders)
{
    for (shared_ptr<Player> player : defenders)
        if (player->get_player_current_score() >= _defenders[0].second ||
            player->get_player_current_score() >= _defenders[1].second)
        {
            _defenders.push_back(make_pair(player->get_player_name(), player->get_player_current_score()));
            sort(_defenders.begin(), _defenders.end(), comp_score);
            _defenders.pop_back();
        }
}

void RealTeam::update_best_goalkeeper(pair<string, double> &_goalkeeper)
{
    for (shared_ptr<Player> player : goalkeepers)
        if (player->get_player_current_score() > _goalkeeper.second ||
            player->get_player_current_score() == _goalkeeper.second && player->get_player_name() < _goalkeeper.first)
        {
            _goalkeeper = make_pair(player->get_player_name(), player->get_player_current_score());
        }
}

void RealTeam::update_best_midfielder(pair<string, double> &_midfielder)
{
    for (shared_ptr<Player> player : midfielders)
        if (player->get_player_current_score() > _midfielder.second ||
            player->get_player_current_score() == _midfielder.second && player->get_player_name() < _midfielder.first)
        {
            _midfielder = make_pair(player->get_player_name(), player->get_player_current_score());
        }
}

void RealTeam::update_best_forward(pair<string, double> &_forward)
{
    for (shared_ptr<Player> player : forwards)
        if (player->get_player_current_score() > _forward.second ||
            player->get_player_current_score() == _forward.second && player->get_player_name() < _forward.first)
        {
            _forward = make_pair(player->get_player_name(), player->get_player_current_score());
        }
}

void RealTeam::print_player(const string &name, const string &position, const double &score)
{
    cout << PRINT_NAME << CHAR_DELIMITER << name << DATA_DELIMITER
         << PRINT_ROLE << CHAR_DELIMITER << position << DATA_DELIMITER
         << PRINT_SCORE << CHAR_DELIMITER << fixed << setprecision(1) << score << endl;
}

bool comp_name(pair<string, double> score1, pair<string, double> score2)
{
    return score1.first < score2.first;
}

bool comp_all_name(WantedPlayers score1, WantedPlayers score2)
{
    return score1.name < score2.name;
}

void RealTeam::print_all_players(bool is_ranked)
{
    map<int, string> position = {{0, GK}, {1, DF}, {2, MD}, {3, FW}};
    vector<WantedPlayers> wanted_players;

    for (int i = 0; i < players.size(); i++)
        wanted_players.push_back({players[i]->get_player_name(), players[i]->get_player_position(), players[i]->get_average_score()});

    if (is_ranked)
        sort(wanted_players.begin(), wanted_players.end(), comp_all_score);
    else
        sort(wanted_players.begin(), wanted_players.end(), comp_all_name);

    cout << LIST_OF_PLAYRES << endl;
    for (int i = 0; i < wanted_players.size(); i++)
    {
        cout << i + 1 << NUMBER_DELIMITER;
        print_player(wanted_players[i].name, position[wanted_players[i].player_position], wanted_players[i].score);
    }
}

void RealTeam::print_players_of_special_position(string position, bool is_ranked)
{
    map<int, string> player_position = {{0, GK}, {1, DF}, {2, MD}, {3, FW}};
    vector<pair<string, double>> wanted_players;

    for (int i = 0; i < players.size(); i++)
    {
        if (position == player_position[players[i]->get_player_position()])
            wanted_players.push_back(make_pair(players[i]->get_player_name(), players[i]->get_average_score()));
    }
    if (is_ranked)
        sort(wanted_players.begin(), wanted_players.end(), comp_score);
    else
        sort(wanted_players.begin(), wanted_players.end(), comp_name);

    cout << LIST_OF_PLAYRES << endl;
    for (int i = 0; i < wanted_players.size(); i++)
    {
        cout << i + 1 << NUMBER_DELIMITER;
        print_player(wanted_players[i].first, position, wanted_players[i].second);
    }
}

LeagueInfo::LeagueInfo(string _team_name, int _goals_for, int _goals_afainst, int _point)
{
    team_name = _team_name;
    goals_for = _goals_for;
    goals_against = _goals_afainst;
    point = _point;
}

int RealTeam::get_goals_for() { return goals_for; }

int RealTeam::get_goals_against() { return goals_against; }

int RealTeam::get_point() { return points; }

shared_ptr<Player> RealTeam::find_player(const string &player_name)
{
    for (shared_ptr<Player> player : players)
        if (player->get_player_name() == player_name)
            return player;

    return NULL;
}