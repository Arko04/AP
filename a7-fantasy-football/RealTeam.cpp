#include "RealTeam.hpp"
#include "Const.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <functional>

string RealTeam::get_team_name()
{
    return team_name;
}

void RealTeam::add_player(vector<pair<string, int>> &players_info,
                          void (RealTeam::*add_player_position)(shared_ptr<Player>),
                          TeamPosition player_position)
{
    for (pair<string, int> player_info : players_info)
    {
        shared_ptr<Player> player = make_shared<Player>(player_info.first, player_position, player_info.second);
        (this->*add_player_position)(player);
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

    goals_for = 0;
    goals_against = 0;
    points = 0;
}

bool is_player_attendded_game(vector<string> team_players, string player_name)
{
    for (int i = 0; i < team_players.size(); i++)
    {
        if (player_name == team_players[i])
            return true;
    }
    return false;
}

void RealTeam::add_players_score(const MatchInfo &match_info, const int &team_index)
{
    int goal_cnt = 0;
    int assist_cnt = 0;
    for (shared_ptr<Player> player : players)
    {
        goal_cnt = 0;
        assist_cnt = 0;
        player->calc_player_score(match_info, team_index);
        if (stoi(match_info.team_goals[1 - team_index]) == 0 &&
            is_player_attendded_game(match_info.team_players[team_index], player->get_player_name()))
            player->set_player_clean_sheets();
        for (int j = 0; j < match_info.goal_with_assist.size(); j++)
        {
            if (player->get_player_name() == match_info.goal_with_assist[j][0] && match_info.goal_with_assist[j][1] != OWN_GOAL)
                goal_cnt++;
            else if (player->get_player_name() == match_info.goal_with_assist[j][1])
                assist_cnt++;
        }
        player->set_player_goal(goal_cnt);
        player->set_player_assists(assist_cnt);
    }
}

double RealTeam::get_player_score(string player_name, vector<vector<string>> scores)
{
    for (vector<string> score : scores)
        if (player_name == score[PLAYER])
            return stod(score[SCORE]);

    return DEFAULT_SCORE;
}

void RealTeam::update_players(const vector<string> &player_names, void (Player::*update_method)())
{
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = 0; j < player_names.size(); j++)
        {
            if (players[i]->get_player_name() == player_names[j])
            {
                (players[i].get()->*update_method)();
            }
        }
    }
}

void RealTeam::update_team(shared_ptr<MatchInfo> match_info, int team_index)
{
    for_each(players.begin(), players.end(), mem_fn(&Player::check_player_availablity));

    update_team_points(stoi(match_info->team_goals[team_index]), stoi(match_info->team_goals[1 - team_index]));
    add_players_score(*match_info, team_index);
    update_players(match_info->injured, &Player::update_injury);
    update_players(match_info->yellow_card, &Player::update_yellow_card);
    update_players(match_info->red_card, &Player::update_red_card);
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

bool comp_all_score(WantedPlayers score1, WantedPlayers score2)
{
    return score1.score > score2.score ||
           score1.score == score2.score && score1.name < score2.name;
}

bool comp_all_name(WantedPlayers score1, WantedPlayers score2)
{
    return score1.name < score2.name;
}

bool comp_name(pair<string, double> score1, pair<string, double> score2)
{
    return (score1.first < score2.first) && (score1.first != "");
}

void RealTeam::update_best_defenders(vector<pair<string, double>> &_defenders)
{
    for (shared_ptr<Player> player : defenders)
    {
        if (player->get_player_current_score() >= _defenders[0].second ||
                 player->get_player_current_score() >= _defenders[1].second)
        {
            _defenders.push_back(make_pair(player->get_player_name(), player->get_player_current_score()));
            sort(_defenders.begin(), _defenders.end(), Utils::comp_score);
            _defenders.pop_back();
            sort(_defenders.begin(), _defenders.end(), comp_name);
        }
    }
}

void RealTeam::update_best_goalkeeper(pair<string, double> &_goalkeeper)
{
    for (shared_ptr<Player> player : goalkeepers)
        update_best_player(player, _goalkeeper);
}

void RealTeam::update_best_midfielder(pair<string, double> &_midfielder)
{
    for (shared_ptr<Player> player : midfielders)
        update_best_player(player, _midfielder);
}

void RealTeam::update_best_forward(pair<string, double> &_forward)
{
    for (shared_ptr<Player> player : forwards)
        update_best_player(player, _forward);
}

void RealTeam::update_best_player(shared_ptr<Player> player, pair<string, double> &_player)
{
    if (player->get_player_current_score() > _player.second ||
        player->get_player_current_score() == _player.second &&
            player->get_player_name() < _player.first)
    {
        _player = make_pair(player->get_player_name(), player->get_player_current_score());
    }
}

void RealTeam::print_player(const WantedPlayers &wanted_player)
{
    map<int, string> position = {{0, GK}, {1, DF}, {2, MD}, {3, FW}};
    double wanted_player_score = floor(wanted_player.score * 10) / 10;

    cout << NAME << CHAR_DELIMITER << wanted_player.name
         << DATA_DELIMITER << ROLE << CHAR_DELIMITER << position[wanted_player.player_position]
         << DATA_DELIMITER << SCORE_STATEMENT << CHAR_DELIMITER << fixed << setprecision(1) << wanted_player_score
         << DATA_DELIMITER << COST << CHAR_DELIMITER << wanted_player.cost;

    if (wanted_player.player_position != GOALKEEPER)
        cout << DATA_DELIMITER << GOALS << CHAR_DELIMITER << wanted_player.goals
             << DATA_DELIMITER << ASSIStS << CHAR_DELIMITER << wanted_player.assists;

    if (wanted_player.player_position != FORWARD)
        cout << DATA_DELIMITER << CLEAN_SHEETS << CHAR_DELIMITER << wanted_player.clean_sheets;

    cout << endl;
}

void RealTeam::print_players(bool is_ranked, string position)
{
    map<int, string> player_position = {{0, GK}, {1, DF}, {2, MD}, {3, FW}};
    vector<WantedPlayers> wanted_players;
    for (int i = 0; i < players.size(); i++)
    {
        if (position == "" || position == player_position[players[i]->get_player_position()])
            wanted_players.push_back(players[i]->get_wanted_player_info());
    }
    if (is_ranked)
        sort(wanted_players.begin(), wanted_players.end(), comp_all_score);
    else
        sort(wanted_players.begin(), wanted_players.end(), comp_all_name);

    cout << LIST_OF_PLAYERS << endl;
    for (int i = 0; i < wanted_players.size(); i++)
    {
        cout << i + 1 << NUMBER_DELIMITER;
        print_player(wanted_players[i]);
    }
}

LeagueInfo::LeagueInfo(string _team_name, int _goals_for, int _goals_afainst, int _point)
{
    team_name = _team_name;
    goals_for = _goals_for;
    goals_against = _goals_afainst;
    point = _point;
}

shared_ptr<Player> RealTeam::find_player(const string &player_name)
{
    for (shared_ptr<Player> player : players)
    {
        if (player->get_player_name() == player_name)
        {
            return player;
        }
    }
    return NULL;
}

LeagueInfo RealTeam::get_league_info()
{
    LeagueInfo league_info(team_name, goals_for, goals_against, points);
    return league_info;
}