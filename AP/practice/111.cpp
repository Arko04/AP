#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;
int main()
{
    string s1, s2;
    cin >> s1 >> s2;

    long long cost[4];
    long long min = 1000000, sum;

    for (int i = 0; i < 4; i++)
        cin >> cost[i];

    map<char, long long> COST = {{'A', cost[0]}, {'C', cost[1]}, {'G', cost[2]}, {'T', cost[3]}};
    for (int i = 0; i <= s1.size() - s2.size(); i++)
    {
        sum = 0;
        for (int j = 0; j < s2.size(); j++)
        {
            if (s1[i + j] != s2[j])
                sum += COST[s2[j]];
        }
        if (sum < min)
        {
            min = sum;
        }
    }
    cout << min << endl;
}