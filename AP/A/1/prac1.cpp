#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef struct note
{
    vector<int> date;
    vector<string> diary;
    int cnt_pwords = 0;
    int sizeStr = 0;
} note;
vector<int> date_initialize();
int main()
{
    // vector<int> dates(3);
    // vector<string> rooz(3, "");
    // int i = 0;
    // while (/*rooz[0].length() < 2 && rooz[1].length() < 2 && */ rooz[2].length() < 4)
    // {
    //     char c = getchar();
    //     switch (c)
    //     {
    //     case '/':
    //         i++;
    //         break;
    //     default:
    //         rooz[i] += c;
    //         break;
    //     }
    // }
    string name = "hillo";
    cout << name.size();
    vector<int> dates(date_initialize());
    for (int x : dates)
    {
        // dates[i] = stoi(rooz[i]); // stoi for converting string to int
        cout << x << ' ';
    }
}

// int main()
// {
//     vector<int> date(3, 0);
//     char ch;
//     int i = 0;
//     while (cin.get(ch))
//     {
//         switch (ch)
//         {
//         case '/':
//             i++;
//             break;
//         default:
//             date[i] = date[i] * 10 + (ch - '0');
//             break;
//         }
//     }

//     return 0;
// }
vector<int> date_initialize()
{
    
    vector<int> dates(3, 0);
    int i = 0;
    char c;
    while (cin.get(c))
    {
        switch (c)
        {
        case '/':
            i++;
            break;
        case '\n':
        case ' ':
            return dates;
        default:
            dates[i] = dates[i] * 10 + (c - '0');
            break;
        }
    }
    return dates;
}

note checkDate(vector<note> notepad, vector<int> time)
{
    for (note diary : notepad)
    {
        if (diary.date == time)
        {
            return diary;
        }
    }
    exit(EXIT_FAILURE);
}
