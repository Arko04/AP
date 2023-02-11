#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<vector<int>> twovd(2, vector<int>(3, 13));
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << twovd[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}