#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool is_correct(const string& p)
{
    int i = 0;
    long unsigned int num = p.size();
    for (long unsigned int j = 0; j < num; j++)
    {
        if (p[j] == '(')
            i++;
        else
            i--;
        if (i < 0)
            return false;
    }
    if (i > 0)
        return false;
    return true;
}

int main()
{
    int n, cnt = 0;
    cin >> n;
    string p;
    cin >> p;
    char c;
    long unsigned int num = p.size();
    for (long unsigned int i = 0; i < num; i++)
    {
        if (is_correct(p))
            cnt++;
        c = p[0];
        p = p.substr(1) + c;
    }
    cout << cnt << endl;
    return 0;
}