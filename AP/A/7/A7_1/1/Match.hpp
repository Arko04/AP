#ifndef _MATCH_
#define _MATCH_
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct MatchInfo
{
    vector<string> teams;
    vector<string> team_goals;
    vector<string> injured;
    vector<string> yellow_card;
    vector<string> red_card;
    vector<vector<string>> score;
};

class Match
{
private:
    string team1;
    string team2;
    int team1_goals;
    int team2_goals;

public:
    Match(shared_ptr<MatchInfo> match_info);
    void test_match_info(shared_ptr<MatchInfo> match_info);
    void remove_trailing_cr(string &s);
};
#endif