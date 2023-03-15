#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool is_letter(char ch)
{
    if (ch >= 'A' && ch <= 'Z' ||
        (ch >= 'a' && ch <= 'z'))
        return true;
    return false;
}
bool palindrome2(string text)
{
    while (true)
    {
        if (text.size() <= 1)
            return true;

        if (!is_letter(text.front()))
        {
            text.erase(text.begin());
            continue;
        }
        if (!is_letter(text.back()))
        {
            text.pop_back();
            continue;
        }
        if (text.front() != text.back() &&
            text.front() != toupper(text.back()) &&
            text.front() != tolower(text.back()))

            return false;
        string new_text(text.begin() + 1, text.end() - 1);
        return palindrome2(new_text);
    }
}
int main()
{
    string text;
    getline(cin, text);

    cout << (palindrome2(text) ? "true" : "false") << endl;

    return 0;
}