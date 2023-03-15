#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<char> letters(26);
    for (int i = 0; i < 26; i++)
        letters[i] = 'A' + i;
    for (char c : letters)
        cout << c << ' ';
    cout << endl;
    return 0;
}