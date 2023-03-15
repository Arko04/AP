#include <iostream>
#include <string>
#include <vector>
using namespace std;
string to_upper(string text)
{
    if (text.empty())
        return "";
    if (text[0] >= 'a' && text[0] <= 'z')
        text[0] = text[0] +  int('A') -int('a')  ;
    return text[0] + to_upper(text.substr(1));
}
int main()
{
    string line;
    string text;
    while (getline(cin, line))
    {
        text += line;
        text += '\n';
    }
    cout << to_upper(text) ;
    return 0;
}

/*
#include <iostream>
#include <string>

using namespace std;

string to_upper(string line){
    if (line == "")
    return "";
    else {
        // if (line[0]<='z' && line[0]>='a'){
        //     line[0]-=32;
        // }
        line[0] = toupper(line[0]);
        return line[0] + to_upper(line.substr(1));
    }

}

int main()
{
    string line;
    while (getline(cin, line))
    {
        cout << to_upper(line) << endl;
    }
    return 0;
}
*/