#include <string>
#include "User.hpp"
#include "Exception.hpp"

User::User(const string &_team_name, const string &_password, const int &_week_num)
    : fantasy_team(_team_name, _week_num)
{
    password = _password;
    sell_count = 2;
    buy_count = 2;
    entered = false;
}

string User::get_user_team_name()
{
    return fantasy_team.get_fantasy_team_name();
}

string User::get_user_password()
{
    return password;
}

void User::handle_new_player(shared_ptr<Player> new_player)
{
    if (new_player->get_playing_status() == false)
    {
        throw PlayerNotAvailable();
    }
    fantasy_team.handle_new_player(new_player);
    buy_count -= (entered) ? 1 : 0;
}

void User::set_transfer_number()
{
    sell_count = 2;
    buy_count = 2;
}

int User::get_sell_count() { return sell_count; }

int User::get_buy_count() { return buy_count; }

pair<string, double> User::get_fantasy_team_info()
{
    return make_pair(fantasy_team.get_fantasy_team_name(), fantasy_team.calc_team_point());
}

void User::handle_sell_player(const string &player_name)
{
    shared_ptr<Player> sold_player = fantasy_team.handle_sell_player(player_name);
    if (sold_player == NULL)
        throw NotFound();

    sell_count -= (entered) ? 1 : 0;
}

string User::get_fantasy_team_name()
{
    return fantasy_team.get_fantasy_team_name();
}

void User::print_squad_command()
{
    if (!fantasy_team.completed())
        throw Empty();
    fantasy_team.print_squad_command();
}

void User::pass_week()
{
    fantasy_team.pass_week();
    
    if (fantasy_team.completed())
        entered = true;
}
bool User::is_entered() { return entered; }