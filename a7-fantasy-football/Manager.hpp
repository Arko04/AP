#ifndef _MANAGER_
#define _MANAGER_
#include <iostream>
#include <vector>
#include <string>
#include "User.hpp"
#include "RealTeam.hpp"
#include "TeamManager.hpp"
#include "WeekManager.hpp"
using namespace std;

class Manager
{
private:
    bool logged_user;
    bool logged_admin;
    bool transfer_window_status;
    shared_ptr<User> active_user;
    vector<shared_ptr<User>> users;
    TeamManager team_manager;
    WeekManager week_manager;
    vector<shared_ptr<RealTeam>> real_teams;
    vector<shared_ptr<Week>> weeks;

    bool is_valid_for_signup(const vector<string> &words);
    bool is_valid_for_login(const vector<string> &words);
    bool is_valid_for_admin_register(const vector<string> &words);
    bool is_valid_for_logout(const vector<string> &words);
    bool is_valid_for_close_transfer_window(const vector<string> &words);
    bool is_valid_for_open_transfer_window(const vector<string> &words);
    bool is_valid_for_pass_week(const vector<string> &words);
    bool is_valid_for_buy_player(const vector<string> &words);
    bool is_valid_for_sell_player(const vector<string> &words);
    bool is_valid_for_squad(const vector<string> &words);
    bool is_valid_for_team_of_the_week(const vector<string> &words);
    bool is_valid_for_players_commnad(const vector<string> &words);
    bool is_valid_for_users_ranking(const vector<string> &words);
    bool is_valid_for_matches_result_league(const vector<string> &words);
    bool is_valid_for_set_captain(const vector<string> &words);
    bool is_valid_for_show_budget();
    bool is_fantasy_team_available(const string &fantasy_team_name);
    bool is_team_name_repetitive(const string &team_name);
    bool is_week_available(const int &week_num);
    bool is_player_in_any_team(const vector<string> &words);
    bool is_position_available(const string &position);
    bool is_team_found(const string &team_name);
    void process_post_command(const vector<string> &words);
    void process_for_signup(const vector<string> &words);
    void process_for_login(const vector<string> &words);
    void process_for_logout(const vector<string> &words);
    void process_for_sell_player(const vector<string> &words);
    void process_for_buy_player(const vector<string> &words);
    void process_for_admin_register(const vector<string> &words);
    void process_for_close_transfer_window(const vector<string> &words);
    void process_for_open_transfer_window(const vector<string> &words);
    void process_for_pass_week(const vector<string> &words);
    void process_for_getting_players_data(string file_name);
    void process_get_command(const vector<string> &words);
    void process_for_team_of_the_week(const vector<string> &words);
    void process_for_players(const vector<string> &words);
    void process_for_league_standings(const vector<string> &words);
    void process_for_users_ranking(const vector<string> &words);
    void process_for_matches_result_league(const vector<string> &words);
    void process_for_squad(const vector<string> &words);
    void process_for_show_budget(const vector<string> &words);
    void process_for_set_captian(const vector<string> &words);
    void process_player_command(const vector<string> &words);
    void update_players_injury();
    void update_team_points();
    void update_player_yellow_card();
    void update_users();
    void update_week_info();
    void add_match_info(shared_ptr<MatchInfo> match_info);
    void add_team_point(vector<pair<shared_ptr<RealTeam>, int>> playing_teams);
    void add_player_injury(vector<string> player_names);
    shared_ptr<User> find_user(const string &team_name);
    shared_ptr<RealTeam> find_real_team(const string &team_name);
    vector<pair<string, double>> find_best_defenders();
    pair<string, double> find_best_goalkeeper();
    pair<string, double> find_best_midfielder();
    pair<string, double> find_best_forward();
    void handle_input(const string &line);
    void handle_league_standing_command();
    void handle_buy_player_command(const string &player_name);
    void handle_sell_player_command(const string &player_name);
    void handle_user_rankings();
    void print_users_ranking(const vector<pair<string, double>> &fantasy_teams);
    void print_matches_result_league(const int &week_num);
    void print_league_info(const vector<LeagueInfo> &league_standings);
    string replace_underscores_with_spaces(string input);
    string get_player_name(const vector<string> &words);
    vector<string> split_by_space(string line);
    void make_best_team_of_the_week();

public:
    Manager(string data_dir);
    void get_input();
};
#endif