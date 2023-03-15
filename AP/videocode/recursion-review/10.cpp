#include <iostream>
#include <string>
#include <vector>
using namespace std;
// int main(){
//     string str;
//     cin >> str;
//     string temp_str = str;
//     reverse(str.begin(), str.end());
//     cout << (temp_str == str ? "true" : "false") << endl;
//     return 0;
// }

bool palindrome(string text)
{
    if (text.size() <= 1)
        return true;
    if (text.front() != text.back())
        return false;
    string new_text(text.begin() + 1, text.end() - 1);
    return palindrome(new_text);
}
int main()
{
    string text;
    getline(cin, text);

    cout << (palindrome(text) ? "true" : "false") << endl;

    return 0;
}