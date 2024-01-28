#include <algorithm>
#include <cmath>
#include <iomanip>
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

    captain = NULL;
}

double FantasyTeam::calc_players_point()
{
    double week_score = DEFAULT_SCORE;
    for (shared_ptr<Player> player : players)
    {
        if (player == captain)
            week_score += player->get_captain_player_score();
        else
            week_score += player->get_player_current_score();
    }
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

bool FantasyTeam::is_position_full(TeamPosition new_player_posiotion)
{
    int position_no = get_position_no(new_player_posiotion);

    return new_player_posiotion != DEFENDER && position_no == 1 ||
           new_player_posiotion == DEFENDER && position_no == 2;
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
            if (sold_player == captain)
                captain = NULL;
            temp_players.erase(temp_players.begin() + i);

            return sold_player;
        }
    }
    return NULL;
}

bool comp_name(shared_ptr<Player> player1, shared_ptr<Player> player2)
{
    return player1->get_player_name() < player2->get_player_name();
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

            if (players[i] == captain)
                cout << CAPTAIN;

            cout << endl;
        }
    }
}

void print_goalkeeper(shared_ptr<Player> player)
{
    cout << GOALKEEPER_ << CHAR_DELIMITER << player->get_player_name();
}

void print_midfielder(shared_ptr<Player> player)
{
    cout << MIDFIELDER_POSITION << CHAR_DELIMITER << player->get_player_name();
}

void print_striker(shared_ptr<Player> player)
{
    cout << STRIKER << CHAR_DELIMITER << player->get_player_name();
}

void FantasyTeam::print_defenders()
{
    vector<shared_ptr<Player>> defenders;
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->get_player_position() == DEFENDER)
            defenders.push_back(players[i]);
    }
    sort(defenders.begin(), defenders.end(), comp_name);

    cout << DEFENDER1 << CHAR_DELIMITER << defenders[0]->get_player_name();
    if (defenders[0] == captain)
        cout << CAPTAIN;
    cout << endl;

    cout << DEFENDER2 << CHAR_DELIMITER << defenders[1]->get_player_name();
    if (defenders[1] == captain)
        cout << CAPTAIN;
    cout << endl;
}

void FantasyTeam::print_squad_command()
{
    cout << FANTASY_TEAM_NAME << CHAR_DELIMITER << fantasy_team_name << endl;

    print_player(GOALKEEPER, print_goalkeeper);
    print_defenders();
    print_player(MIDFIELDER, print_midfielder);
    print_player(FORWARD, print_striker);

    double point = calc_team_point();
    point = floor(point * 10) / 10;
    cout << TOTAL_POINT << CHAR_DELIMITER << fixed << setprecision(1) << point << endl;
    int team_cost = calc_team_cost();
    cout << TEAM_COST << CHAR_DELIMITER << team_cost << endl;
}

double FantasyTeam::calc_team_point()
{
    double point = DEFAULT_SCORE;
    for (double week_score : week_scores)
        point += week_score;

    return point;
}

int FantasyTeam::calc_team_cost()
{
    int team_cost = 0;
    for (shared_ptr<Player> player : players)
    {
        team_cost += player->get_cost();
    }

    return team_cost;
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

void FantasyTeam::handle_set_captain(const string &player_name)
{
    if (captain != NULL)
        throw BadRequest();

    for (shared_ptr<Player> player : temp_players)
        if (player_name == player->get_player_name())
        {
            captain = player;
            return;
        }

    throw NotFound();
}