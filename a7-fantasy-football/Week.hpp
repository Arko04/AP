#ifndef _WEEK_
#define _WEEK_
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "RealTeam.hpp"
#include "Match.hpp"

struct BestTeam
{
    pair<string, double> goalkeeper;
    vector<pair<string, double>> defenders;
    pair<string, double> midfielder;
    pair<string, double> forward;
};

class Week
{
private:
    vector<shared_ptr<Match>> matches;
    vector<shared_ptr<MatchInfo>> matches_info;
    shared_ptr<BestTeam> best_team;

    void print_player_of_the_week(string position, pair<string, double> player);

public:
    Week(vector<shared_ptr<MatchInfo>> _matches_info);
    vector<shared_ptr<MatchInfo>> get_matches_info();
    void add_best_team(shared_ptr<BestTeam> _best_team);
    void display_best_team_of_the_week();
    void print_matches_result_league();
};
#endif