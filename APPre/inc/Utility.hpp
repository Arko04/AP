#ifndef _UTILITY_
#define _UTILITY_

#include <iostream>
#include <vector>
using namespace std;

class Utility
{
public:
    bool static is_integer(const string token);
    static vector<string> split_by(string token, const char &del);
};

#endif