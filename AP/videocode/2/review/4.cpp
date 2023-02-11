#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<char> characters(100, 'A');
    for (int i = 0; i < characters.size(); i++)
        cout << characters[i];
    return 0;
}
