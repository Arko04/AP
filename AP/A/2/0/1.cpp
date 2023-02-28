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