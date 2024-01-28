#ifndef _PLAYER_
#define _PLAYER_
#include <iostream>
#include <memory>
#include <vector>
#include "Score.hpp"
using namespace std;

enum TeamPosition
{
    GOALKEEPER = 0,
    DEFENDER = 1,
    MIDFIELDER = 2,
    FORWARD = 3

};

struct WantedPlayers
{
    string name;
    TeamPosition player_position;
    double score;
    int goals;
    int assists;
    int clean_sheets;
    int cost;
};

class Player
{
private:
    string name;
    double week_score;
    double total_score;
    TeamPosition player_position;
    int yellow_card_count;
    int injured_count;
    int attend_game_number;
    int off_week;
    bool is_playing;
    int cost;
    int goals;
    int assists;
    int clean_sheets;
    shared_ptr<Score> player_score;

public:
    Player(string _name, TeamPosition _position, int _cost);
    void check_player_availablity();
    void update_injury();
    void update_red_card();
    void update_yellow_card();
    bool get_playing_status();
    double get_player_current_score();
    double get_captain_player_score();
    int get_yellow_card();
    string get_player_name();
    double get_average_score();
    TeamPosition get_player_position();
    void set_player_score(double score);
    void add_attendent_game();
    void set_player_goal(int _goals);
    void set_player_assists(int _assists);
    void set_player_clean_sheets();
    int get_cost();
    void calc_player_score(const MatchInfo &match_info, const int &team_index);
    WantedPlayers get_wanted_player_info();
};
#endif