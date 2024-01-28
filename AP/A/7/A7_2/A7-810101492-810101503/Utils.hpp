#ifndef _UTILS_
#define _UTILS_
#include <iostream>
#include <vector>
using namespace std;

class Utils
{
public:
    static vector<string> split_by(const char &delimiter, string &line);
    static string remove_backslash_r(string s);
    static double calc_player_score(const double &init_score);
    static bool comp_score(pair<string, double> score1, pair<string, double> score2);
};

#endif