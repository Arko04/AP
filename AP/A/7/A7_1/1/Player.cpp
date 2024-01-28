#include <vector>
#include "Player.hpp"
#include "Const.hpp"

string Player::remove_backslash_r(string s)
{
    if (!s.empty() && s.back() == '\r')
        s.pop_back();

    return s;
}

void Player::set_player_name(string s)
{
    this->name = s;
}

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

Player::Player(string _name, TeamPosition _player_position)
{
    name = _name;
    player_position = _player_position;
    week_score = 0.0;
    total_score = 0.0;
    yellow_card_count = 0;
    injured_count = 0;
    is_playing = true;
    off_week = 0;
    attend_game_number = 0;
}

void Player::set_player_off_week(int _off_week)
{
    off_week = _off_week;
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
    this->yellow_card_count = this->yellow_card_count + 1;
    if (this->yellow_card_count == MAX_LEGAL_YELLOW_CARD)
    {
        off_week = max(off_week, OFF_WEEK_FOR_YELLOW_CARD);
        this->yellow_card_count = 0;
    }
}

void Player::update_red_card()
{
    off_week = max(off_week, OFF_WEEK_FOR_RED_CARD);
    this->yellow_card_count = 0;
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

void Player::set_yellow_card_zero()
{
    this->yellow_card_count = 0;
}

int Player::get_yellow_card()
{
    return yellow_card_count;
}

bool Player::check_needed_yellow_card_player(vector<string> yellow_cards)
{
    int yellow_card_flag = 0;
    for (int i = 0; i < yellow_cards.size(); i++)
    {
        if (yellow_cards[i] == this->name)
            yellow_card_flag = 1;
    }
    if (yellow_card_flag == 1)
        return false;
    return true;
}

TeamPosition Player::get_player_position()
{
    return player_position;
}

bool Player::get_playing_status() { return is_playing; }