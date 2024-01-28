#ifndef _PLAYER_
#define _PLAYER_
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

enum TeamPosition
{
    GOALKEEPER = 0,
    DEFENDER = 1,
    MIDFIELDER = 2,
    FORWARD = 3
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

public:
    Player(string _name, TeamPosition _position);
    bool check_needed_yellow_card_player(vector<string> yellow_cards);
    void check_player_availablity();
    void update_red_card();
    void update_yellow_card();
    bool get_playing_status();
    double get_player_current_score();
    int get_yellow_card();
    string get_player_name();
    double get_average_score();
    TeamPosition get_player_position();
    void set_player_score(double score);
    void set_player_name(string s);
    void set_yellow_card_zero();
    void set_player_off_week(int _off_week);
    void add_attendent_game();
    string remove_backslash_r(string s);
};
#endif