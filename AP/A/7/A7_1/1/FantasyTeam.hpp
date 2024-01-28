#ifndef _FANTASY_TEAM_
#define _FANTASY_TEAM_
#include <iostream>
#include <memory>
#include <vector>
#include "Player.hpp"
using namespace std;
class FantasyTeam
{
private:
    string fantasy_team_name;
    vector<shared_ptr<Player>> players;
    vector<shared_ptr<Player>> temp_players;
    vector<double> week_scores;

    void update_fantasy_team_points();
    double calc_players_point();
    int get_position_no(const TeamPosition &team_position);

    void print_defenders();
    void print_player(TeamPosition player_position, void(print_player_position)(shared_ptr<Player>));
    bool is_position_full(TeamPosition new_player_position);

public:
    bool completed();
    double calc_team_point();
    FantasyTeam(const string &_name, const int &week_num);
    string get_fantasy_team_name();
    void handle_new_player(shared_ptr<Player> new_player);
    shared_ptr<Player> handle_sell_player(const string &player_name);
    string get_team_name();
    void print_squad_command();
    void pass_week();
};
#endif