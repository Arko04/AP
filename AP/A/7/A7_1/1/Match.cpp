#include "Match.hpp"
#include "Const.hpp"

Match::Match(shared_ptr<MatchInfo> match_info)
{
    team1 = match_info->teams[0];
    team2 = match_info->teams[1];
    team1_goals = stoi(match_info->team_goals[0]);
    team2_goals = stoi(match_info->team_goals[1]);
    remove_trailing_cr(match_info->score.back()[1]);
}

void Match::remove_trailing_cr(string &s)
{
    if (!s.empty() && s.back() == '\r')
        s.pop_back();
}

void Match::test_match_info(shared_ptr<MatchInfo> match_info)
{
    cout << TEAM_GOALS_ARE << CHAR_DELIMITER << endl;
    cout << TEAM1 << CHAR_DELIMITER << team1 << endl;
    cout << TEAM2 << CHAR_DELIMITER << team2 << endl;
    cout << TEAM_GOALS_ARE << CHAR_DELIMITER << endl;
    cout << TEAM_GOAL1 << CHAR_DELIMITER << team1_goals << endl;
    cout << TEAM_GOAL2 << CHAR_DELIMITER << team2_goals << endl;
    cout << INJURED_PLAYERS_ARE << CHAR_DELIMITER << endl;

    for (int i = 0; i < match_info->injured.size(); i++)
        cout << match_info->injured[i] << endl;

    cout << YELLOW_CARD_PLAYERS_ARE << CHAR_DELIMITER << endl;
    for (int i = 0; i < match_info->yellow_card.size(); i++)
        cout << match_info->yellow_card[i] << endl;

    cout << RED_CARD_PLAYERS_ARE << CHAR_DELIMITER << endl;
    for (int i = 0; i < match_info->red_card.size(); i++)
        cout << match_info->red_card[i] << endl;

    cout << SCORES_FOR_PLAYERS_ARE << CHAR_DELIMITER << endl;
    for (int i = 0; i < match_info->score.size(); i++)
        for (int j = 0; j < match_info->score[i].size(); j++)
            cout << PLAYER_SCORE << CHAR_DELIMITER << match_info->score[i][j] << endl;
}