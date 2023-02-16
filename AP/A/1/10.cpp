#include <iostream>
#include <string>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
// inputFile.tellg()!=-1
//  #include <iterator>
using namespace std;

vector<string> reading_file_positive_words(string filename);

typedef struct note
{
    int no_best_words = 0;
    int size = 0;
    string date;
    vector<string> diary;
} note;

note maxsize(vector<note> notepad)
{
    int ret_val = 0;
    note longest_diary;
    for (note temp_diary : notepad)
    {
        if (temp_diary.size > ret_val)
        {
            ret_val = temp_diary.size;
            longest_diary = temp_diary;
        }
    }
    return longest_diary;
}
note maxbestwords(vector<note> notepad)
{
    int ret_val = 0;
    note best_diary;
    for (note temp_diary : notepad)
    {
        if (temp_diary.no_best_words > ret_val)
        {
            ret_val = temp_diary.no_best_words;
            best_diary = temp_diary;
        }
    }
    return best_diary;
}
void printnote(note notes)
{
    int cnt = 0;
    cout << notes.date << " ";
    vector<string> content = notes.diary;
    for (string word : content)
    {
        if (cnt + word.size() < 20) // why it should'nt be equal to 20
        {
            cout << word << " ";
            cnt += word.size() + 1;
        }
        else
        {
            char *letters = strdup(word.c_str()); // transforming string to char*
            for (int i = 0; cnt < 20; cnt++, i++)
            { // why it should'nt be equal to 20
                cout << letters[i];
            }
            break;
        }
    }
    if (cnt >= 20)
        cout << "...";
}

int main()
{
    string input;
    note diary;
    vector<note> notepad;

    vector<string> best_Words;

    ifstream inputFile;
    inputFile.open("positive-words.txt");
    string word;
    while (getline(inputFile, word))
    {
        best_Words.push_back(word);
    }

    inputFile.close();

    // for(string i : best_Words)
    // cout<<i<<'\n';

    while (cin >> input)
    {
        if (input == "start_day")
        {
            notepad.push_back(diary);
            cin >> input;
            notepad.back().date = input;
        }
        else if (input == "show_day")
        {
            cin >> input;
            for (int i = 0; i < notepad.size(); i++)
            {
                if (notepad[i].date == input)
                {
                    for (string word : notepad[i].diary)
                    {
                        cout << word << " ";
                    }
                }
            }
        }
        else if (input == "show_the_longest_day")
        {
            note ret = maxsize(notepad);
            printnote(ret);
        }
        else if (input == "show_the_best_day")
        {
            note ret = maxbestwords(notepad);
            printnote(ret);
        }
        else
        { // note
            notepad.back().diary.push_back(input);
            notepad.back().size += input.size();
            // it should be 'iterator' i think. i maen instead of 'auto'
            int status = 0;
            for (string x : best_Words)
            {
                while (1)
                {
                    string chech = "\\b";
                    chech += input;
                    chech += '\\b';
                    int status = input.find(chech, status);
                    if (status != string::npos)
                    {
                        notepad.back().no_best_words++;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }
}
//returns a vector including positive-words
vector<string> reading_file_positive_words(string filename) // positive-words.txt
{
    fstream input;
    string word;
    vector<string> positive_words;
    input.open(filename);
    while (getline(input, word))
        positive_words.push_back(word);
    input.close();
    return positive_words;
}