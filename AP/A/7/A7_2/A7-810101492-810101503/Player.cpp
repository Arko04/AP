#include <vector>
#include <cmath>
#include "Player.hpp"
#include "Const.hpp"
#include "Utils.hpp"

void Player::add_attendent_game()
{
    attend_game_number++;
}

string Player::get_player_name()
{
    return name;
}

double Player::get_average_score()
{
    return (attend_game_number != 0) ? total_score / attend_game_number : DEFAULT_SCORE;
}

Player::Player(string _name, TeamPosition _player_position, int _cost)
{
    name = _name;
    player_position = _player_position;
    cost = _cost;
    week_score = 0;
    total_score = 0;
    yellow_card_count = 0;
    injured_count = 0;
    is_playing = true;
    off_week = 0;
    attend_game_number = 0;
    clean_sheets = 0;
    assists = 0;
    goals = 0;
}

void Player::set_player_goal(int _goals)
{
    goals += _goals;
}

void Player::set_player_assists(int _assists)
{
    assists += _assists;
}

void Player::set_player_clean_sheets()
{
    clean_sheets++;
}

void Player::calc_player_score(const MatchInfo &match_info, const int &team_index)
{
    player_score = Score::set_score_calculator(match_info.team_players[team_index], name);
    week_score = player_score->calc_score(match_info, team_index, name);

    if (week_score != DEFAULT_SCORE)
    {
        total_score += week_score;
        attend_game_number++;
    }
}

int Player::get_cost()
{
    return cost;
}

void Player::update_injury()
{
    off_week = OFF_WEEK_FOR_INJURY;
}

void Player::set_player_score(double score)
{
    week_score = score;
    total_score += score;
}

double Player::get_player_current_score()
{
    return this->week_score;
}

void Player::update_yellow_card()
{
    yellow_card_count = yellow_card_count + 1;
    if (yellow_card_count == MAX_LEGAL_YELLOW_CARD)
    {
        off_week = max(off_week, OFF_WEEK_FOR_YELLOW_CARD);
        yellow_card_count = 0;
    }
}
void Player::update_red_card()
{
    off_week = max(off_week, OFF_WEEK_FOR_RED_CARD);
    yellow_card_count = 0;
}
void Player::check_player_availablity()
{
    if (off_week != 0)
    {
        is_playing = false;
        off_week--;
    }
    else
        is_playing = true;
}

int Player::get_yellow_card()
{
    return yellow_card_count;
}

TeamPosition Player::get_player_position()
{
    return player_position;
}

bool Player::get_playing_status() { return is_playing; }

WantedPlayers Player::get_wanted_player_info()
{
    WantedPlayers wanted_player;

    wanted_player.name = this->name;
    wanted_player.player_position = this->player_position;
    wanted_player.score = this->get_average_score();
    wanted_player.goals = this->goals;
    wanted_player.assists = this->assists;
    wanted_player.clean_sheets = this->clean_sheets;
    wanted_player.cost = this->cost;

    return wanted_player;
}

double Player::get_captain_player_score()
{
    return player_score->get_captain_score();
}