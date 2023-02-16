#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
// #include <algorithm>
// inputFile.tellg()!=-1
//  #include <iterator>
using namespace std;

#define DAY 0
#define MONTH 1
#define YEAR 2

typedef struct note
{
    vector<int> date{0, 0, 0};
    string diary = "";
    int cnt_pwords = 0;
    int sizeStr = 0;
} note;

vector<string> reading_file_positive_words(string filename);

int count_positive_words(string line, vector<string> positive_words);
int countMatchInRegex(string line, string word);

void dateInit(vector<int> &time);

note checkDate(vector<note> notepad, vector<int> time);

note checkLongest(vector<note> notepad);

note checkBest(vector<note> notepad);

void printNote(note text);

void addNote(string input, vector<string> positve_words, vector<note> &notepad);

int main(void)
{
    vector<string> positive_words = reading_file_positive_words("positive-words.txt");
    string input, line;
    vector<note> notepad;
    note check_note;
    vector<int> temp_day(3);
    while (cin >> input)
    {
        if (input == "start_day")
        {
            notepad.resize(notepad.size() + 1);
            dateInit(notepad.back().date);
            // for (int x : temp_diary.date)
            //     cout << x << '/';
        }
        else if (input == "show_day")
        {
            dateInit(temp_day);
            check_note = checkDate(notepad, temp_day);
            cout << check_note.diary; //

            // for (int x : temp_diary.date)
            //     cout << x << '/';
        }
        else if (input == "show_the_longest_day")
        {
            check_note = checkLongest(notepad);
            cout << check_note.date[DAY] << '/' << check_note.date[MONTH] << '/' << check_note.date[YEAR] << '\n';
            printNote(check_note);
        }
        else if (input == "show_the_best_day")
        {
            check_note = checkBest(notepad);
            cout << check_note.date[DAY] << '/' << check_note.date[MONTH] << '/' << check_note.date[YEAR] << '\n';
            printNote(check_note);
        }
        else
        {
            addNote(input, positive_words, notepad);
            // line = input;
            // getline(cin, input);
            // line += input;
            // // cout << line;
            // notepad.back().sizeStr += line.size();
            // notepad.back().cnt_pwords += count_positive_words(line, positive_words);
            // notepad.back().diary += line;
            // notepad.back().diary += '\n';
        }
    }
    // for (string x : positive_words)
    //     cout << x << '\n';

    return 0;
}

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

int countMatchInRegex(string text, string word)
{
    regex words_regex(word);
    auto words_begin = sregex_iterator(text.begin(), text.end(), words_regex);
    auto words_end = sregex_iterator();

    return distance(words_begin, words_end);
}

void dateInit(vector<int> &time)
{
    getchar();
    vector<int> dates(3, 0);
    int i = 0;
    char c;
    while (cin.get(c))
    {
        switch (c)
        {
        case '/':
            time[i] = dates[i];
            i++;
            break;
        case '\n':
        case ' ':
            time[i] = dates[i];
            return;
        default:
            dates[i] = dates[i] * 10 + (c - '0');
            break;
        }
    }
    return;
}

int count_positive_words(string line, vector<string> positive_words)
{
    transform(line.begin(), line.end(), line.begin(),::tolower); /// converting to lowercase
    int cnt_pwords = 0;
    for (string word : positive_words)
    {
        cnt_pwords += countMatchInRegex(line, word);
    }
    return cnt_pwords;
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

note checkLongest(vector<note> notepad)
{
    int max_val = 0;
    note longest_diary;
    for (note temp_diary : notepad)
    {
        if (temp_diary.sizeStr > max_val)
        {
            max_val = temp_diary.sizeStr;
            longest_diary = temp_diary;
        }
    }
    return longest_diary;
}

note checkBest(vector<note> notepad)
{
    int max_val = 0;
    note best_diary;
    for (note temp_diary : notepad)
    {
        if (temp_diary.cnt_pwords > max_val)
        {
            max_val = temp_diary.cnt_pwords;
            best_diary = temp_diary;
        }
    }
    // cout << max_val;////////
    return best_diary;
}

void printNote(note text)
{
    int cnt_letters = 0;
    vector<char> letters(text.diary.begin(), text.diary.end());
    for (char ch : letters)
    {
        if (cnt_letters < 20)
        {
            cout << ch;
            cnt_letters++;
        }
        else
        {
            cout << "...\n";
            return;
        }
    }
    cout << '\n';
    return;
}
//
void addNote(string input, vector<string> positive_words, vector<note> &notepad)
{
    string line = input;
    getline(cin, input);
    line += input;
    // cout << line;
    notepad.back().sizeStr += line.size();
    notepad.back().cnt_pwords += count_positive_words(line, positive_words);
    notepad.back().diary += line;
    notepad.back().diary += '\n';
}
//
