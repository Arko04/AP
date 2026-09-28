#ifndef _SCORE_
#define _SCORE_
#include <iostream>
#include "Match.hpp"
using namespace std;
class Score
{
protected:
    bool has_scored_goal(const string &player_name, const vector<string> &goal_with_assist);
    virtual double init_attending_score(const MatchInfo &match_info, const int &team_index, const string &player_name);
    double raw_score;
    
public:
    Score() {}
    static shared_ptr<Score> set_score_calculator(vector<string> team_players, const string &player_name);
    virtual double calc_score(const MatchInfo &match_info, const int &team_index, const string &player_name) = 0;
    virtual double get_captain_score();
};

class DefenderScore : public Score
{
protected:
    virtual double init_attending_score(const MatchInfo &match_info, const int &team_index, const string &player_name);
    
public:
    DefenderScore() {}
    virtual double calc_score(const MatchInfo &match_info, const int &team_index, const string &player_name) = 0;
};

class GoalkeeperScore : public Score
{
private:
public:
    GoalkeeperScore() {}
    virtual double calc_score(const MatchInfo &match_info, const int &team_index, const string &player_name);
};

class CenterDefenderScore : public DefenderScore
{
private:
public:
    CenterDefenderScore() {}
    virtual double calc_score(const MatchInfo &match_info, const int &team_index, const string &player_name);
};

class RightDefenderScore : public DefenderScore
{
private:
public:
    RightDefenderScore() {}
    virtual double calc_score(const MatchInfo &match_info, const int &team_index, const string &player_name);
};

class LeftDefenderScore : public DefenderScore
{
private:
public:
    LeftDefenderScore() {}
    virtual double calc_score(const MatchInfo &match_info, const int &team_index, const string &player_name);
};

class MidFielderScore : public Score
{
private:
public:
    MidFielderScore() {}
    virtual double calc_score(const MatchInfo &match_info, const int &team_index, const string &player_name);
};

class ForwardScore : public Score
{
private:
public:
    ForwardScore() {}
    virtual double calc_score(const MatchInfo &match_info, const int &team_index, const string &player_name);
};

class NotAttendedScore : public Score
{
private:
public:
    virtual double get_captain_score();
    NotAttendedScore() {}
    virtual double calc_score(const MatchInfo &match_info, const int &team_index, const string &player_name);
};
#endif