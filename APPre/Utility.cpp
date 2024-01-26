#include "Utility.hpp"
#include "Const.hpp"
#include <sstream>

bool Utility::is_integer(const string token)
{
    for (int i = 0; i < token.size(); i++)
    {
        // cout << (char(48));
        // cout << (char(57));
        if (token[i] >= START_NUM && token[i] <= END_NUM)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

vector<string> Utility::split_by(string token, char del)
{
    stringstream input(token);
    string part;
    vector<string> tokens;
    // int answers_count = 0;
    while (getline(input, part, del))
    {
        if (part != EMPTY)
        {
            tokens.push_back(part);
        }
    }
    return tokens;
}