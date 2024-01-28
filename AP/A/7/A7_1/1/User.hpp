#ifndef _USER_
#define _USER_
#include <iostream>
#include <string>
#include <vector>
#include "FantasyTeam.hpp"
using namespace std;
class User
{
private:
    FantasyTeam fantasy_team;
    string password;
    int sell_count;
    int buy_count;
    bool entered;

public:
    User();
    User(const string &team_name, const string &password, const int &week_num);
    string get_user_team_name();
    string get_user_password();
    void handle_new_player(shared_ptr<Player> new_player);
    void set_transfer_number();
    int get_sell_count();
    int get_buy_count();
    void handle_sell_player(const string &player_name);
    pair<string, double> get_fantasy_team_info();
    string get_fantasy_team_name();
    void print_squad_command();
    void pass_week();
    bool is_entered();
};
#endif