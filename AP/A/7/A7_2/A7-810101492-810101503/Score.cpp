#include "Score.hpp"
#include "Const.hpp"
#include "Utils.hpp"

enum Goal
{
    GoalScorer = 0,
    GoalAssister = 1
};
enum Players
{
    GoalKeeper = 0,
    LeftDefender = 1,
    LeftCenterDefender = 2,
    RightCenterDefender = 3,
    RightDefender = 4,
    LeftMidfielder = 5,
    CenterMidfielder = 6,
    RightMidfielder = 7,
    LeftForward = 8,
    CenterForward = 9,
    RightForward = 10
};

double Score::init_attending_score(const MatchInfo &match_info, const int &team_index, const string &player_name)
{
    double score = DEFAULT_SCORE;

    for (vector<string> goal_with_assist : match_info.goal_with_assist)
    {
        if (player_name == goal_with_assist[GoalScorer] &&
            goal_with_assist[GoalAssister] == OWN_GOAL)
            score += OWN_GOAL_SCORE;
    }
    if (match_info.team_goals[team_index] > match_info.team_goals[1 - team_index])
        score += WIN_SCORE;
    else if (match_info.team_goals[team_index] == match_info.team_goals[1 - team_index])
        score += DRAW_SCORE;
    else
        score += LOSE_SCROE;

    return score;
}

double GoalkeeperScore::calc_score(const MatchInfo &match_info,
                                   const int &team_index,
                                   const string &player_name)
{
    double score = init_attending_score(match_info, team_index, player_name) + INIT_GK_SCORE;

    int goal_against = stoi(match_info.team_goals[1 - team_index]);
    score = (goal_against == 0) ? score + GK_CLEAN_SHEET_SCORE : score - double(goal_against);

    raw_score = score;
    return Utils::calc_player_score(raw_score);
}

double CenterDefenderScore::calc_score(const MatchInfo &match_info,
                                       const int &team_index,
                                       const string &player_name)
{
    double score = init_attending_score(match_info, team_index, player_name);
    
    vector<string> rival = match_info.team_players[1 - team_index];
    for (vector<string> goal_with_assist : match_info.goal_with_assist)
    {
        if (has_scored_goal(rival[LeftCenterDefender], goal_with_assist) ||
            has_scored_goal(rival[RightCenterDefender], goal_with_assist) ||
            has_scored_goal(rival[CenterForward], goal_with_assist))
            score -= 1;
    }
    raw_score = score;
    return Utils::calc_player_score(raw_score);
}

double RightDefenderScore::calc_score(const MatchInfo &match_info,
                                      const int &team_index,
                                      const string &player_name)
{
    double score = init_attending_score(match_info, team_index, player_name);

    vector<string> rival = match_info.team_players[1 - team_index];
    for (vector<string> goal_with_assist : match_info.goal_with_assist)
    {
        if (has_scored_goal(rival[LeftDefender], goal_with_assist) ||
            has_scored_goal(rival[LeftForward], goal_with_assist))
            score -= 1;
    }
    raw_score = score;
    return Utils::calc_player_score(raw_score);
}

double LeftDefenderScore::calc_score(const MatchInfo &match_info,
                                     const int &team_index,
                                     const string &player_name)
{
    double score = init_attending_score(match_info, team_index, player_name);

    vector<string> rival = match_info.team_players[1 - team_index];
    for (vector<string> goal_with_assist : match_info.goal_with_assist)
    {
        if (has_scored_goal(rival[RightDefender], goal_with_assist) ||
            has_scored_goal(rival[RightForward], goal_with_assist))
            score -= 1;
    }
    raw_score = score;
    return Utils::calc_player_score(raw_score);
}

double DefenderScore::init_attending_score(const MatchInfo &match_info,
                                           const int &team_index,
                                           const string &player_name)
{
    double score = Score::init_attending_score(match_info, team_index, player_name) + INIT_DF_SCORE;
    int goal_against = stoi(match_info.team_goals[1 - team_index]);
    score += (goal_against == 0) ? DF_CLEAN_SHEET_SCORE : 0;

    for (vector<string> goal_with_assist : match_info.goal_with_assist)
    {
        if (has_scored_goal(player_name, goal_with_assist))
            score += DF_GOAL_SCORE;
        else if (player_name == goal_with_assist[GoalAssister])
            score += DF_ASSIST_SCORE;
    }
    return score;
}

double MidFielderScore::calc_score(const MatchInfo &match_info,
                                   const int &team_index,
                                   const string &player_name)
{
    double score = init_attending_score(match_info, team_index, player_name);
    int goal_against = stoi(match_info.team_goals[1 - team_index]);
    score += (goal_against == 0) ? MD_CLEAN_SHEET_SCORE : 0;

    vector<string> rival = match_info.team_players[1 - team_index];
    for (vector<string> goal_with_assist : match_info.goal_with_assist)
    {
        if (has_scored_goal(player_name, goal_with_assist))
            score += MD_GOAL_SCORE;
        else if (player_name == goal_with_assist[GoalAssister])
            score += MD_ASSIST_SCORE;

        if (has_scored_goal(rival[LeftMidfielder], goal_with_assist) ||
            has_scored_goal(rival[CenterMidfielder], goal_with_assist) ||
            has_scored_goal(rival[RightMidfielder], goal_with_assist))
            score -= 1;
    }
    raw_score = score;
    return Utils::calc_player_score(raw_score);
}

double ForwardScore::calc_score(const MatchInfo &match_info,
                                const int &team_index,
                                const string &player_name)
{
    double score = init_attending_score(match_info, team_index, player_name);
    bool has_scored = false;

    for (vector<string> goal_with_assist : match_info.goal_with_assist)
    {
        if (has_scored_goal(player_name, goal_with_assist))
        {
            score += FW_GOAL_SCORE;
            has_scored = true;
        }
        else if (player_name == goal_with_assist[GoalAssister])
            score += FW_ASSIST_SCORE;
    }
    if (has_scored == false)
        score -= 1;

    raw_score = score;
    return Utils::calc_player_score(raw_score);
}

double NotAttendedScore::calc_score(const MatchInfo &match_info, const int &team_index, const string &player_name)
{
    return DEFAULT_SCORE;
}

shared_ptr<Score> Score::set_score_calculator(vector<string> team_players, const string &player_name)
{
    if (team_players[GoalKeeper] == player_name)
        return make_shared<GoalkeeperScore>();
    else if (team_players[LeftDefender] == player_name)
        return make_shared<LeftDefenderScore>();
    else if (team_players[LeftCenterDefender] == player_name ||
             team_players[RightCenterDefender] == player_name)
        return make_shared<CenterDefenderScore>();
    else if (team_players[RightDefender] == player_name)
        return make_shared<RightDefenderScore>();
    else if (team_players[LeftMidfielder] == player_name ||
             team_players[CenterMidfielder] == player_name ||
             team_players[RightMidfielder] == player_name)
        return make_shared<MidFielderScore>();
    else if (team_players[LeftForward] == player_name ||
             team_players[CenterForward] == player_name ||
             team_players[RightForward] == player_name)
        return make_shared<ForwardScore>();
    else
        return make_shared<NotAttendedScore>();
}

bool Score::has_scored_goal(const string &player_name, const vector<string> &goal_with_assist)
{
    return player_name == goal_with_assist[GoalScorer] &&
           goal_with_assist[GoalAssister] != OWN_GOAL;
}

double Score::get_captain_score()
{
    return Utils::calc_player_score(raw_score * 2);
}

double NotAttendedScore::get_captain_score()
{
    return DEFAULT_SCORE;
}