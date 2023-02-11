#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main()
{
    int i;
    vector<string> words;
    string temp_word;
    while (cin >> temp_word)
        words.push_back(temp_word);
    cout << '[';
    for (i = 0; i < words.size() - 1; i++)
        cout << words[i] << ", ";
    cout << words[i] << "]\n";
    return 0;
}