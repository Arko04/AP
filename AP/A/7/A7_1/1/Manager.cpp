#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>
#include "Manager.hpp"
#include "Exception.hpp"
#include "Const.hpp"
using namespace std;

Manager::Manager(string data_dir)
    : team_manager(data_dir), week_manager(data_dir + ADDR_DELIMITER + WEEK_DIR)
{
    real_teams = team_manager.get_real_teams();
    logged_user = false;
    logged_admin = false;
    transfer_window_status = true;
}

vector<string> Manager::split_by_space(string line)
{
    istringstream iss(line);
    vector<string> words(istream_iterator<string>{iss},
                         istream_iterator<string>());
    return words;
}

bool Manager::is_valid_for_signup(const vector<string> &words)
{
    if (words.size() != EXPECTED_ARGUMENTS_NO_FOR_SIGNUP)
        return false;

    if (logged_admin == true)
        throw PermissionDenied();
    else if (logged_user == true)
        return false;

    string mark = words[2];
    string team_name_statement = words[3];
    string password_statement = words[5];

    if (mark != INPUT_MARK || team_name_statement != TEAM_NAME || password_statement != PASSWORD)
        return false;

    return true;
}

bool Manager::is_valid_for_login(const vector<string> &words)
{
    if (words.size() != EXPECTED_ARGUMENTS_NO_FOR_LOGIN)
        return false;

    if (logged_admin == true)
        throw PermissionDenied();
    else if (logged_user == true)
        return false;

    string mark = words[2];
    string team_name_statement = words[3];
    string password_statement = words[5];

    if (mark != INPUT_MARK || team_name_statement != TEAM_NAME || password_statement != PASSWORD)
        return false;

    return true;
}

bool Manager::is_team_name_repetitive(const string &team_name)
{
    for (int user_no = 0; user_no < users.size(); user_no++)
        if (users[user_no]->get_user_team_name() == team_name)
            return true;

    return false;
}

shared_ptr<User> Manager::find_user(const string &team_name)
{
    for (int user_no = 0; user_no < users.size(); user_no++)
        if (users[user_no]->get_user_team_name() == team_name)
            return users[user_no];

    return NULL;
}

void Manager::process_for_signup(const vector<string> &words)
{
    if (!is_valid_for_signup(words))
        throw BadRequest();

    string team_name = words[4];
    string password = words[6];

    if (is_team_name_repetitive(team_name))
        throw BadRequest();

    shared_ptr<User> new_user = make_shared<User>(team_name, password, weeks.size());
    users.push_back(new_user);
    logged_user = true;
    active_user = new_user;

    cout << OK << endl;
}

void Manager::process_for_login(const vector<string> &words)
{
    if (!is_valid_for_login(words))
        throw BadRequest();

    string team_name = words[4];
    string password = words[6];

    shared_ptr<User> user = find_user(team_name);
    if (user == NULL)
        throw NotFound();
    else if (user->get_user_password() != password)
        throw PermissionDenied();
    else
    {
        logged_user = true;
        active_user = user;
    }
    cout << OK << endl;
}

bool Manager::is_valid_for_admin_register(const vector<string> &words)
{
    if (words.size() != EXPECTED_ARGUMENTS_NO_FOR_REGISTER_ADMIN)
        return false;

    string mark = words[2];
    string user_name_statement = words[3];
    string user_name = words[4];
    string password_statement = words[5];
    string password = words[6];

    if (mark != INPUT_MARK || user_name_statement != USERNAME || password_statement != PASSWORD)
        return false;
    else if (logged_admin == false && logged_user == false &&
             user_name == ADMIN_USERNAME && password == ADMIN_PASSWORD)
        return true;
    else
        return false;
}

void Manager::handle_buy_player_command(const string &player_name)
{
    if (active_user->get_buy_count() == 0)
        throw PermissionDenied();

    for (shared_ptr<RealTeam> real_team : real_teams)
    {
        shared_ptr<Player> wanted_player = real_team->find_player(player_name);
        if (wanted_player != NULL)
        {
            active_user->handle_new_player(wanted_player);
            return;
        }
    }

    throw NotFound();
}

void Manager::process_for_admin_register(const vector<string> &words)
{
    if (!is_valid_for_admin_register(words))
        throw BadRequest();

    logged_admin = true;
    cout << OK << endl;
}

bool Manager::is_valid_for_logout(const vector<string> &words)
{
    if (words.size() != EXPECTED_ARGUMENTS_NO_FOR_LOGOUT)
        return false;

    return true;
}

void Manager::process_for_logout(const vector<string> &words)
{
    if (!is_valid_for_logout(words))
        throw BadRequest();

    if (logged_admin == true)
        logged_admin = false;
    else if (logged_user == true)
        logged_user = false;
    else
        throw PermissionDenied();

    cout << OK << endl;
}

bool Manager::is_valid_for_close_transfer_window(const vector<string> &words)
{
    if (words.size() != EXPECTED_ARGUMENTS_NO_FOR_CLOSE_TRANSFER_WINDOW)
        return false;

    if (logged_admin != true)
        throw PermissionDenied();

    return true;
}

bool Manager::is_valid_for_open_transfer_window(const vector<string> &words)
{
    if (words.size() != EXPECTED_ARGUMENTS_NO_FOR_OPEN_TRANSFER_WINDOW)
        return false;

    if (logged_admin != true)
        throw PermissionDenied();
    return true;
}

void Manager::process_for_close_transfer_window(const vector<string> &words)
{
    if (!is_valid_for_close_transfer_window(words))
        throw BadRequest();

    transfer_window_status = false;

    cout << OK << endl;
}

void Manager::process_for_open_transfer_window(const vector<string> &words)
{
    if (!is_valid_for_open_transfer_window(words))
        throw BadRequest();

    transfer_window_status = true;

    cout << OK << endl;
}

bool Manager::is_valid_for_pass_week(const vector<string> &words)
{
    if (words.size() != EXPECTED_ARGUMENTS_NO_FOR_PASS_WEEK)
        return false;

    if (logged_admin != true)
        throw PermissionDenied();
    return true;
}

void Manager::update_users()
{
    for (shared_ptr<User> user : users)
    {
        user->set_transfer_number();
        user->pass_week();
    }
}

void Manager::process_for_pass_week(const vector<string> &words)
{
    if (!is_valid_for_pass_week(words))
        throw BadRequest();

    shared_ptr<Week> week = make_shared<Week>(*week_manager.pass_week());
    weeks.push_back(week);
    update_week_info();
    update_users();

    cout << OK << endl;
}

void Manager::add_match_info(shared_ptr<MatchInfo> match_info)
{
    for (int i = 0; i < match_info->teams.size(); i++)
    {
        shared_ptr<RealTeam> real_team = find_real_team(match_info->teams[i]);
        real_team->update_team(match_info, i);
    }
}

void Manager::update_week_info()
{
    vector<shared_ptr<MatchInfo>> matches_info = weeks.back()->get_matches_info();

    for (shared_ptr<MatchInfo> match_info : matches_info)
        add_match_info(match_info);

    make_best_team_of_the_week();
}

void Manager::make_best_team_of_the_week()
{
    shared_ptr<BestTeam> best_team = make_shared<BestTeam>();

    best_team->goalkeeper = find_best_goalkeeper();
    best_team->defenders = find_best_defenders();
    best_team->midfielder = find_best_midfielder();
    best_team->forward = find_best_forward();

    weeks.back()->add_best_team(best_team);
}

vector<pair<string, double>> Manager::find_best_defenders()
{
    vector<pair<string, double>> defenders = {{"", DEFAULT_SCORE}, {"", DEFAULT_SCORE}};

    for (shared_ptr<RealTeam> real_team : real_teams)
        real_team->update_best_defenders(defenders);

    return defenders;
}

pair<string, double> Manager::find_best_goalkeeper()
{
    pair<string, double> goalkeeper = {"", DEFAULT_SCORE};
    for (shared_ptr<RealTeam> real_team : real_teams)
        real_team->update_best_goalkeeper(goalkeeper);

    return goalkeeper;
}

pair<string, double> Manager::find_best_midfielder()
{
    pair<string, double> midfielder = {"", DEFAULT_SCORE};
    for (shared_ptr<RealTeam> real_team : real_teams)
        real_team->update_best_midfielder(midfielder);

    return midfielder;
}

pair<string, double> Manager::find_best_forward()
{
    pair<string, double> forward = {"", DEFAULT_SCORE};
    for (shared_ptr<RealTeam> real_team : real_teams)
        real_team->update_best_forward(forward);

    return forward;
}

shared_ptr<RealTeam> Manager::find_real_team(const string &team_name)
{
    for (shared_ptr<RealTeam> real_team : real_teams)
        if (real_team->get_team_name() == team_name)
            return real_team;

    return NULL;
}

bool Manager::is_valid_for_buy_player(const vector<string> &words)
{
    if (words.size() <= EXPECTED_ARGUMENTS_NO_FOR_BUY_PLAYER)
        return false;
    if (transfer_window_status == false)
        throw PermissionDenied();

    if (logged_user != true)
        throw PermissionDenied();

    string mark = words[2];
    if (mark != INPUT_MARK)
        return false;
    string name = words[3];
    if (name != NAME)
        return false;
    return true;
}

string Manager::get_player_name(const vector<string> &words)
{
    string new_player_name = "";
    for (int i = 4; i < words.size(); i++)
        new_player_name += words[i] + " ";

    new_player_name.pop_back();
    return new_player_name;
}

void Manager::process_for_buy_player(const vector<string> &words)
{
    if (!is_valid_for_buy_player(words))
        throw BadRequest();

    string new_player_name = get_player_name(words);
    handle_buy_player_command(new_player_name);

    cout << OK << endl;
}

bool compare_teams(const LeagueInfo &team1, const LeagueInfo &team2)
{
    if (team1.point != team2.point)
        return team1.point > team2.point;
    else if (team1.goals_for - team1.goals_against != team2.goals_for - team2.goals_against)
        return team1.goals_for - team1.goals_against > team2.goals_for - team2.goals_against;
    else if (team1.goals_for != team2.goals_for)
        return team1.goals_for > team2.goals_for;
    else
        return team1.team_name < team2.team_name;
}

void Manager::handle_league_standing_command()
{
    vector<LeagueInfo> league_standings;
    for (int i = 0; i < real_teams.size(); i++)
    {
        LeagueInfo league_info(real_teams[i]->get_team_name(),
                               real_teams[i]->get_goals_for(),
                               real_teams[i]->get_goals_against(),
                               real_teams[i]->get_point());
        league_standings.push_back(league_info);
    }
    sort(league_standings.begin(), league_standings.end(), compare_teams);
    print_league_info(league_standings);
}

bool Manager::is_valid_for_sell_player(const vector<string> &words)
{
    if (words.size() <= EXPECTED_ARGUMENTS_NO_FOR_SELL_PLAYER)
        return false;
    if (transfer_window_status == false)
        throw PermissionDenied();

    if (logged_user != true)
        throw PermissionDenied();

    string mark = words[2];
    if (mark != INPUT_MARK)
        return false;
    string name = words[3];
    if (name != NAME)
        return false;
    return true;
}

void Manager::handle_sell_player_command(const string &player_name)
{
    if (active_user->get_sell_count() == 0)
        throw PermissionDenied();
    active_user->handle_sell_player(player_name);
}

void Manager::process_for_sell_player(const vector<string> &words)
{
    if (!is_valid_for_sell_player(words))
        throw BadRequest();

    string new_player_name = get_player_name(words);
    handle_sell_player_command(new_player_name);

    cout << OK << endl;
}

void Manager::process_post_command(const vector<string> &words)
{
    string command = words[1];
    if (command == SIGNUP)
        process_for_signup(words);
    else if (command == LOGIN)
        process_for_login(words);
    else if (command == REDGISTER_ADMIN)
        process_for_admin_register(words);
    else if (command == LOGOUT)
        process_for_logout(words);
    else if (command == CLOSE_TRANSFER_WINDOW)
        process_for_close_transfer_window(words);
    else if (command == OPEN_TRANSFER_WINDOW)
        process_for_open_transfer_window(words);
    else if (command == PASS_WEEK)
        process_for_pass_week(words);
    else if (command == BUY_PLAYER)
        process_for_buy_player(words);
    else if (command == SELL_PLAYER)
        process_for_sell_player(words);
    else
        throw BadRequest();
}

void Manager::get_input()
{
    string line;
    while (getline(cin, line))
    {
        try
        {
            handle_input(line);
        }
        catch (const NotFound &e)
        {
            cout << NOT_FOUND << endl;
        }
        catch (const BadRequest &e)
        {
            cout << BAD_REQUEST << endl;
        }
        catch (const PlayerNotAvailable &e)
        {
            cout << PLAYER_NOT_AVAILABLE << endl;
        }
        catch (const PermissionDenied &e)
        {
            cout << PERMISSION_DENIED << endl;
        }
        catch (const Empty &e)
        {
            cout << EMPTY << endl;
        }
        catch (const invalid_argument &e)
        {
            cout << BAD_REQUEST << endl;
        }
    }
}

bool Manager::is_week_available(const int &week_num)
{
    return week_num > 0 && week_num <= weeks.size();
}

bool Manager::is_valid_for_team_of_the_week(const vector<string> &words)
{
    if (words.size() != MIN_EXPECTED_ARGUMENTS_NO_FOR_TEAM_OF_THE_WEEK &&
        words.size() != MAX_EXPECTED_ARGUMENTS_NO_FOR_TEAM_OF_THE_WEEK)
        return false;

    string mark = words[2];
    if (mark != INPUT_MARK)
        return false;

    if (words.size() == MAX_EXPECTED_ARGUMENTS_NO_FOR_TEAM_OF_THE_WEEK)
    {
        string week_num_statement = words[3];
        int week_number = stoi(words[4]);

        if (week_num_statement != WEEK_NUM)
            return false;
        if (!is_week_available(week_number))
            return false;
    }
    return true;
}

void Manager::process_for_team_of_the_week(const vector<string> &words)
{
    if (!is_valid_for_team_of_the_week(words))
        throw BadRequest();
    int week_num = 0;
    if (words.size() == MIN_EXPECTED_ARGUMENTS_NO_FOR_TEAM_OF_THE_WEEK)
        week_num = weeks.size() - 1;
    else
        week_num = stoi(words[4]) - 1;

    if (week_num >= 0)
        weeks[week_num]->display_best_team_of_the_week();
    else
        throw BadRequest();
}

bool Manager::is_position_available(const string &position)
{
    if (position != GK && position != DF && position != MD && position != FW)
        return false;

    return true;
}

bool Manager::is_team_found(const string &team_name)
{
    for (int i = 0; i < real_teams.size(); i++)
        if (team_name == real_teams[i]->get_team_name())
            return true;

    return false;
}

string Manager::replace_underscores_with_spaces(string input)
{
    for (int i = 0; i < input.length(); i++)
        if (input[i] == TEAM_NAME_DELIMITER)
            input[i] = SPACE;

    return input;
}

bool Manager::is_valid_for_players_commnad(const vector<string> &words)
{
    if (words.size() < MIN_EXPECTED_ARGUMENTS_NO_FOR_PLAYERS ||
        words.size() > MAX_EXPECTED_ARGUMENTS_NO_FOR_PLAYERS)
        return false;

    string team_name_statement = words[3];
    if (team_name_statement != TEAM_NAME)
        return false;

    string mark = words[2];
    if (mark != INPUT_MARK)
        return false;

    if (words.size() == 6)
    {
        if (!is_position_available(words[5]) && words[5] != RANKS)
            return false;
    }
    if (words.size() == MAX_EXPECTED_ARGUMENTS_NO_FOR_PLAYERS)
    {
        if (words[6] != RANKS)
            return false;
    }
    string team_name = replace_underscores_with_spaces(words[4]);
    if (!is_team_found(team_name))
        throw NotFound();

    return true;
}

void Manager::print_league_info(const vector<LeagueInfo> &league_standings)
{
    cout << LEAGUE_STANDING << MATCH_DELIMITER << endl;
    for (int i = 0; i < league_standings.size(); i++)
    {
        cout << i + 1 << NUMBER_DELIMITER << league_standings[i].team_name << CHAR_DELIMITER
             << PRINT_SCORE << CHAR_DELIMITER << league_standings[i].point << DATA_DELIMITER
             << GF << CHAR_DELIMITER << league_standings[i].goals_for << DATA_DELIMITER
             << GA << CHAR_DELIMITER << league_standings[i].goals_against << endl;
    }
}

void Manager::process_player_command(const vector<string> &words)
{
    string team_name = words[4];
    string wanted_team_name = replace_underscores_with_spaces(team_name);

    shared_ptr<RealTeam> real_team = find_real_team(wanted_team_name);

    if (words.size() == MIN_EXPECTED_ARGUMENTS_NO_FOR_PLAYERS || (words.size() == 6 && words[5] == RANKS))
        real_team->print_all_players(words.size() == 6);
    else
    {
        string status = words[5];
        real_team->print_players_of_special_position(status, words.size() ==
                                                                 MAX_EXPECTED_ARGUMENTS_NO_FOR_PLAYERS);
    }
}

void Manager::process_for_players(const vector<string> &words)
{
    if (!is_valid_for_players_commnad(words))
        throw BadRequest();

    process_player_command(words);
}

bool Manager::is_valid_for_users_ranking(const vector<string> &words)
{
    if (words.size() != EXPECTED_ARGUMENTS_NO_FOR_USERS_RANKINGS)
        return false;

    return true;
}

void Manager::process_for_league_standings(const vector<string> &words)
{
    if (words.size() != EXPECTED_ARGUMENTS_NO_FOR_LEAGUE_STANDINGS)
        throw BadRequest();
    handle_league_standing_command();
}

bool compare_fantasy_teams(pair<string, double> &fantasy_team1, pair<string, double> &fantasy_team2)
{
    if (fantasy_team1.second != fantasy_team2.second)
    {
        return fantasy_team1.second > fantasy_team2.second;
    }
    return fantasy_team1.first < fantasy_team2.first;
}

void Manager::print_users_ranking(const vector<pair<string, double>> &fantasy_teams)
{
    for (int i = 0; i < fantasy_teams.size(); i++)
    {
        cout << i + 1 << NUMBER_DELIMITER << TEAM_NAME << CHAR_DELIMITER << fantasy_teams[i].first << DATA_DELIMITER
             << POINT << CHAR_DELIMITER << fantasy_teams[i].second << endl;
    }
}

void Manager::handle_user_rankings()
{
    vector<pair<string, double>> fantasy_teams;
    for (shared_ptr<User> user : users)
    {
        if (user->is_entered())
            fantasy_teams.push_back(user->get_fantasy_team_info());
    }
    if (fantasy_teams.empty())
        throw Empty();
    sort(fantasy_teams.begin(), fantasy_teams.end(), compare_fantasy_teams);
    print_users_ranking(fantasy_teams);
}

void Manager::process_for_users_ranking(const vector<string> &words)
{
    if (!is_valid_for_users_ranking(words))
        throw BadRequest();
    handle_user_rankings();
}

bool Manager::is_valid_for_matches_result_league(const vector<string> &words)
{
    if (words.size() != MIN_EXPECTED_ARGUMENTS_NO_FOR_MATCHES_RESULT_LEAGUE &&
        words.size() != MAX_EXPECTED_ARGUMENTS_NO_FOR_MATCHES_RESULT_LEAGUE)
        return false;

    string mark = words[2];
    if (mark != INPUT_MARK)
        return false;

    if (words.size() == MAX_EXPECTED_ARGUMENTS_NO_FOR_MATCHES_RESULT_LEAGUE)
    {
        string week_num_statement = words[3];
        int week_num = stoi(words[4]);
        if (week_num_statement != WEEK_NUM)
            return false;
        if (!is_week_available(week_num))
            return false;
    }
    return true;
}

void Manager::print_matches_result_league(const int &week_num)
{
    for (int i = 0; i < weeks.size(); i++)
        if (i == week_num - 1)
            weeks[i]->print_matches_result_league();
}

void Manager::process_for_matches_result_league(const vector<string> &words)
{
    if (!is_valid_for_matches_result_league(words))
        throw BadRequest();

    int week_num = stoi(words[4]);
    print_matches_result_league(week_num);
}

bool Manager::is_fantasy_team_available(const string &fantasy_team_name)
{
    for (int i = 0; i < users.size(); i++)
        if (users[i]->get_fantasy_team_name() == fantasy_team_name)
            return true;

    return false;
}

bool Manager::is_valid_for_squad(const vector<string> &words)
{
    if (words.size() != MIN_EXPECTED_ARGUMENTS_NO_FOR_SQUAD &&
        words.size() != MAX_EXPECTED_ARGUMENTS_NO_FOR_SQUAD)
        return false;

    string mark = words[2];
    if (mark != INPUT_MARK)
        return false;

    if (logged_user != true)
        throw PermissionDenied();

    if (words.size() == MAX_EXPECTED_ARGUMENTS_NO_FOR_SQUAD)
    {
        string fantasy_team_name_statement = words[3];
        if (fantasy_team_name_statement != FANTASY_TEAM_NAME)
            return false;
    }
    return true;
}

void Manager::process_for_squad(const vector<string> &words)
{
    if (!is_valid_for_squad(words))
        throw BadRequest();
    if (words.size() == MIN_EXPECTED_ARGUMENTS_NO_FOR_SQUAD)
        active_user->print_squad_command();

    if (words.size() == MAX_EXPECTED_ARGUMENTS_NO_FOR_SQUAD)
    {
        string fantasy_team_name = words[4];
        shared_ptr<User> user = find_user(fantasy_team_name);
        if (user == NULL)
            throw NotFound();

        user->print_squad_command();
    }
}

void Manager::process_get_command(const vector<string> &words)
{
    string command = words[1];
    if (command == TEAM_OF_THE_WEEK)
        process_for_team_of_the_week(words);
    else if (command == PLAYERS)
        process_for_players(words);
    else if (command == LEAGUE_STANDINGS)
        process_for_league_standings(words);
    else if (command == USERS_RANKING)
        process_for_users_ranking(words);
    else if (command == MATCHES_RESULT_LEAGUE)
        process_for_matches_result_league(words);
    else if (command == SQUAD)
        process_for_squad(words);
    else
        throw BadRequest();
}

void Manager::handle_input(const string &line)
{

    vector<string> words = split_by_space(line);
    if (words.empty())
        throw BadRequest();

    string command = words[0];
    if (command == POST)
        process_post_command(words);
    else if (command == GET)
        process_get_command(words);
    else
        throw BadRequest();
}