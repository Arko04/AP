// ali's code
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int t;
    cin >> t;
    for (; t > 0; t--)
    {
        string c, m, d;
        cin >> c >> m >> d;
        bool c1 = false;
        bool c2 = false;
        bool c3 = false;
        bool c4 = false;
        bool c5 = false;
        bool c6 = false;
        bool p = true;
        if (c.find('A') != std::string::npos || m.find('A') != std::string::npos)
        {
            c1 = true;
        }
        if (c.find('B') != std::string::npos || m.find('B') != std::string::npos)
        {
            c2 = true;
        }
        if (c.find('+') != std::string::npos || m.find('+') != std::string::npos)
        {
            c3 = true;
        }
        if (d.find('A') != std::string::npos)
        {
            c4 = true;
        }
        if (d.find('B') != std::string::npos)
        {
            c5 = true;
        }
        if (d.find('+') != std::string::npos)
        {
            c6 = true;
        }
        if ((!c1 && c4) || (!c2 && c5) || (!c3 && c6))
        {
            p = false;
        }
        if (p)
        {
            cout << "valid\n";
        }
        else
        {
            cout << "invalid\n";
        }
    }
}
