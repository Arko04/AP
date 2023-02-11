#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<vector<int>> v(4);
    v[0].push_back(3);
    v[0].push_back(12);
    v[1].push_back(6);
    v[3].push_back(2);
    v[3].push_back(8);
    v[3].push_back(5);
    for (int i = 0; i < 4; i++)
    {
        for (int x : v[i])
            cout << x << ' ';
        cout << '\n';
    }
    return 0;
}