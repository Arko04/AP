#include <sstream>
#include <cmath>
#include "Utils.hpp"

vector<string> Utils::split_by(const char &delimiter, string &line)
{
    stringstream input(line);
    string token;
    vector<string> tokens;

    while (getline(input, token, delimiter))
        tokens.push_back(token);

    return tokens;
}

string Utils::remove_backslash_r(string s)
{
    if (!s.empty() && s.back() == '\r')
        s.pop_back();

    return s;
}

double Utils::calc_player_score(const double &init_score)
{
    double denominator = 1 + exp(-init_score / 6);
    double result_score = 10 / denominator;
    return result_score;
}

bool Utils::comp_score(pair<string, double> score1, pair<string, double> score2)
{
    return score1.second > score2.second ||
           score1.second == score2.second && score1.first < score2.first;
}