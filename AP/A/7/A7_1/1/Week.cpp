#include "Week.hpp"
#include "Const.hpp"

Week::Week(vector<shared_ptr<MatchInfo>> _matches_info)
{
    matches_info = _matches_info;
    for (shared_ptr<MatchInfo> match_info : _matches_info)
    {
        shared_ptr<Match> match = make_shared<Match>(match_info);
        matches.push_back(match);
    }
}

vector<shared_ptr<MatchInfo>> Week::get_matches_info()
{
    return matches_info;
}

void Week::add_best_team(shared_ptr<BestTeam> _best_team)
{
    best_team = _best_team;
}

void Week::print_player_of_the_week(string position, pair<string, double> player)
{
    cout << position << CHAR_DELIMITER
         << player.first << DATA_DELIMITER
         << PRINT_SCORE << CHAR_DELIMITER
         << player.second << endl;
}
void Week::display_best_team_of_the_week()
{

    cout << PRINT_TEAM_OF_THE_WEEK << CHAR_DELIMITER << endl;

    print_player_of_the_week(GOALKEEPER_POSITION, best_team->goalkeeper);
    print_player_of_the_week(DEFENDER1_POSITION, best_team->defenders[0]);
    print_player_of_the_week(DEFENDER2_POSITION, best_team->defenders[1]);
    print_player_of_the_week(MIDFIELDER_POSITION, best_team->midfielder);
    print_player_of_the_week(FORWARD_POSITION, best_team->forward);
}

void Week::print_matches_result_league()
{
    for (int i = 0; i < matches_info.size(); i++)
    {
        cout << matches_info[i]->teams[0] << SPACE << matches_info[i]->team_goals[0] << DATA_DELIMITER
             << matches_info[i]->teams[1] << SPACE << matches_info[i]->team_goals[1] << endl;
    }
}