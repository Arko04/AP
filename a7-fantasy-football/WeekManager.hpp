#ifndef _WEEK_MANAGER_
#define _WEEK_MANAGER_
#include <iostream>
#include <memory>
#include "Week.hpp"
using namespace std;

class WeekManager
{
private:
    int week_index;
    string filename;

    shared_ptr<MatchInfo> parse_match_info(string line);

public:
    WeekManager(const string &_filename);
    shared_ptr<Week> pass_week();
    vector<vector<string>> get_scores(string field);
};
#endif