#include <algorithm>
#include "FantasyTeam.hpp"
#include "Exception.hpp"
#include "Const.hpp"

string FantasyTeam::get_fantasy_team_name()
{
    return fantasy_team_name;
}

FantasyTeam::FantasyTeam(const string &_name, const int &week_num)
{
    fantasy_team_name = _name;

    for (int i = 0; i <= week_num; i++)
        week_scores.push_back(DEFAULT_SCORE);
}

double FantasyTeam::calc_players_point()
{
    double week_score = DEFAULT_SCORE;
    for (shared_ptr<Player> player : players)
        week_score += player->get_player_current_score();

    return week_score;
}

void FantasyTeam::update_fantasy_team_points()
{
    if (!week_scores.empty())
    {
        if (players.size() == 5)
            week_scores.back() = calc_players_point();
        else
            week_scores.back() = DEFAULT_SCORE;
    }
}

bool FantasyTeam::is_position_full(TeamPosition new_player_position)
{
    int position_no = get_position_no(new_player_position);

    return new_player_position != DEFENDER && position_no == 1 ||
           new_player_position == DEFENDER && position_no == 2;
}

void FantasyTeam::handle_new_player(shared_ptr<Player> new_player)
{
    if (is_position_full(new_player->get_player_position()))
        throw BadRequest();

    for (shared_ptr<Player> player : temp_players)
        if (new_player->get_player_name() == player->get_player_name())
            throw PermissionDenied();

    temp_players.push_back(new_player);
}

int FantasyTeam::get_position_no(const TeamPosition &team_position)
{
    int position_cnt = 0;
    for (shared_ptr<Player> player : temp_players)
        if (player->get_player_position() == team_position)
            position_cnt++;

    return position_cnt;
}

shared_ptr<Player> FantasyTeam::handle_sell_player(const string &player_name)
{
    for (int i = 0; i < temp_players.size(); i++)
    {
        if (player_name == temp_players[i]->get_player_name())
        {
            shared_ptr<Player> sold_player = temp_players[i];
            temp_players.erase(temp_players.begin() + i);
            return sold_player;
        }
    }
    return NULL;
}

bool comp_name(string player1_name, string player2_name)
{
    return player1_name < player2_name;
}

string FantasyTeam::get_team_name() { return fantasy_team_name; }

void FantasyTeam::print_player(TeamPosition player_position,
                               void(print_player_position)(shared_ptr<Player>))
{
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->get_player_position() == player_position)
        {
            (*print_player_position)(players[i]);
        }
    }
}

void print_goalkeeper(shared_ptr<Player> player)
{
    cout << GOALKEEPER_ << CHAR_DELIMITER << player->get_player_name() << endl;
}

void print_midfielder(shared_ptr<Player> player)
{
    cout << MIDFIELDER_POSITION << CHAR_DELIMITER << player->get_player_name() << endl;
}

void print_striker(shared_ptr<Player> player)
{
    cout << STRIKER << CHAR_DELIMITER << player->get_player_name() << endl;
}

void FantasyTeam::print_defenders()
{
    vector<string> defender_names;
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->get_player_position() == DEFENDER)
            defender_names.push_back(players[i]->get_player_name());
    }
    sort(defender_names.begin(), defender_names.end(), comp_name);
    cout << DEFENDER1 << CHAR_DELIMITER << defender_names[0] << endl;
    cout << DEFENDER2 << CHAR_DELIMITER << defender_names[1] << endl;
}

void FantasyTeam::print_squad_command()
{
    cout << FANTASY_TEAM_NAME << CHAR_DELIMITER << fantasy_team_name << endl;

    print_player(GOALKEEPER, print_goalkeeper);
    print_defenders();
    print_player(MIDFIELDER, print_midfielder);
    print_player(FORWARD, print_striker);

    double point = calc_team_point();
    cout << TOTAL_POINT << CHAR_DELIMITER << point << endl;
}

double FantasyTeam::calc_team_point()
{
    double point = DEFAULT_SCORE;
    for (double week_score : week_scores)
        point += week_score;

    return point;
}

void FantasyTeam::pass_week()
{
    players = temp_players;
    update_fantasy_team_points();
    week_scores.push_back(DEFAULT_SCORE);
}

bool FantasyTeam::completed()
{
    return players.size() == 5;
}