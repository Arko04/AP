#ifndef _REALTEAM_
#define _REALTEAM_
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Player.hpp"
#include "Match.hpp"
using namespace std;

struct TeamInfo
{
    string team_name;
    vector<string> goalkeepers, defenders, midfielders, forwards;
};

struct LeagueInfo
{
    LeagueInfo(string _team_name, int _goals_for, int _goals_afainst, int _score);
    string team_name;
    int goals_for;
    int goals_against;
    int point;
};

class RealTeam
{
private:
    string team_name;
    vector<shared_ptr<Player>> goalkeepers;
    vector<shared_ptr<Player>> defenders;
    vector<shared_ptr<Player>> midfielders;
    vector<shared_ptr<Player>> forwards;
    vector<shared_ptr<Player>> players;
    int goals_for;
    int goals_against;
    int points;

    double get_player_score(string player_name, vector<vector<string>> scores);

public:
    RealTeam(TeamInfo team_info);
    void delete_last_character(shared_ptr<Player> player);
    void add_players_score(vector<vector<string>> scores);
    void add_player_injury(const vector<string> &player_names);
    void update_player_yellow_card(const vector<string> &player_names);
    void update_player_red_card(const vector<string> &player_names);
    void update_injured_players(const vector<string> &injured);
    void update_team(shared_ptr<MatchInfo> match_info, int team_index);
    void update_team_points(const int &_goals_for, const int &_goals_against);
    void update_best_defenders(vector<pair<string, double>> &defenders);
    void update_best_goalkeeper(pair<string, double> &goalkeeper);
    void update_best_midfielder(pair<string, double> &midfielder);
    void update_best_forward(pair<string, double> &forward);
    void print_all_players(bool is_ranked);
    void print_players_of_special_position(string position, bool is_ranked);
    void print_player(const string &name, const string &position, const double &score);
    string get_team_name();
    int get_goals_for();
    int get_goals_against();
    int get_point();
    shared_ptr<Player> find_player(const string &player_name);
    string remove_backslash_r(string s);
    void add_player(vector<string> &players, void (RealTeam::*add_player)(shared_ptr<Player>), TeamPosition player_position);
    void add_goalkeeper(shared_ptr<Player> goalkeeper);
    void add_defender(shared_ptr<Player> defender);
    void add_midfielder(shared_ptr<Player> midfielder);
    void add_forward(shared_ptr<Player> forward);
};
#endif