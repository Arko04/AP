#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

using namespace std;

#define DAY 0
#define MONTH 1
#define YEAR 2

#define DATE_DELIMITER '/'
#define MAX_LEN 20

typedef struct note
{
    vector<int> date{DAY, MONTH, YEAR};
    int positive_word_count = 0;
    int diary_length = 0;
    string diary = "";
} note;

vector<string> reading_file_positive_words(string file_name);

void start_day(vector<note>& notepad);

void show_day(vector<note> notepad, note& searched_note, vector <int>& searched_day);

void show_the_longest_day(vector<note> notepad, note& longest_note);

void show_the_best_day(vector<note> notepad, note& best_note);

bool is_positive(string input_word, vector<string> positive_words);

void date_initialize(vector<int> &time);

note check_date(vector<note> notepad, vector<int> time);

note check_longest_note(vector<note> notepad);

note check_best_note(vector<note> notepad);

int compare_date(vector<int> date1, vector<int> date2);

void print_note(note text);

void add_note(string input, vector<string> positve_words, vector<note> &notepad);

int main(void)
{
    vector<string> positive_words = reading_file_positive_words("positive-words.txt");
    string input;
    vector<note> notepad;
    note check_note;
    vector<int> temp_day(3);

    while (cin >> input)
    {
        if (input == "start_day")
        {
            start_day(notepad);
            // notepad.resize(notepad.size() + 1);
            // date_initialize(notepad.back().date);
        }
        else if (input == "show_day")
        {
            show_day(notepad, check_note, temp_day);
            // date_initialize(temp_day);
            // check_note = check_date(notepad, temp_day);
            // cout << check_note.diary;
        }
        else if (input == "show_the_longest_day")
        {
            // check_note = check_longest_note(notepad);
            // cout << check_note.date[DAY] << DATE_DELIMITER << check_note.date[MONTH] << DATE_DELIMITER << check_note.date[YEAR] << endl;
            // print_note(check_note);
            show_the_longest_day(notepad, check_note);
        }
        else if (input == "show_the_best_day")
        {
            // check_note = check_best_note(notepad);
            // cout << check_note.date[DAY] << DATE_DELIMITER << check_note.date[MONTH] << DATE_DELIMITER << check_note.date[YEAR] << endl;
            // print_note(check_note);
            show_the_best_day(notepad, check_note);
        }
        else
            add_note(input, positive_words, notepad);
    }
    exit(EXIT_SUCCESS);
}

vector<string> reading_file_positive_words(string file_name)
{
    ifstream input;
    string word;
    vector<string> positive_words;

    input.open(file_name);

    while (input >> word)
        positive_words.push_back(word);

    input.close();
    return positive_words;
}

void start_day(vector<note>& notepad)
{
    notepad.resize(notepad.size() + 1);
    date_initialize(notepad.back().date);
}

void show_day(vector<note> notepad, note& searched_note, vector <int>& searched_day)
{
    // note searched_note;
    // vector<int> searched_day(3,0);

    date_initialize(searched_day);
    cout << searched_day[0]<< DATE_DELIMITER<< searched_day[1]<< DATE_DELIMITER <<searched_day[2]<<endl;
    searched_note = check_date(notepad, searched_day);

    cout << searched_note.diary;
}

void show_the_longest_day(vector<note> notepad, note& longest_note)
{
    longest_note = check_longest_note(notepad);

    cout << longest_note.date[DAY] << DATE_DELIMITER << longest_note.date[MONTH] << DATE_DELIMITER << longest_note.date[YEAR] << endl;
    
    print_note(longest_note);
}

void show_the_best_day(vector<note> notepad, note& best_note)
{
    best_note = check_best_note(notepad);

    cout << best_note.date[DAY] << DATE_DELIMITER << best_note.date[MONTH] << DATE_DELIMITER << best_note.date[YEAR] << endl;
    
    print_note(best_note);
}
void date_initialize(vector<int> &time)
{
    vector<int> dates(3, 0);
    int i = 0;
    char letter;

    getchar();

    while (cin.get(letter))
    {
        switch (letter)
        {
        case DATE_DELIMITER:
            time[i] = dates[i];
            i++;
            break;
        case '\n':
        case ' ':
            time[i] = dates[i];
            return;
        default:
            dates[i] = dates[i] * 10 + (letter - '0');
            break;
        }
    }
    return;
}

bool is_positive(string input_word, vector<string> positive_words)
{
    for (string word : positive_words)
    {
        if (input_word.compare(word) == 0)
            return true;
    }
    return false;
}

note check_date(vector<note> notepad, vector<int> time)
{
    for (note diary : notepad)
    {
        if (diary.date == time)
            return diary;
    }
    exit(EXIT_FAILURE);
}

note check_longest_note(vector<note> notepad)
{
    int max_size = 0;
    note longest_diary;

    for (note temp_diary : notepad)
    {
        if (temp_diary.diary_length > max_size)
        {
            max_size = temp_diary.diary_length;
            longest_diary = temp_diary;
        }
        else if (temp_diary.diary_length == max_size)
        {
            if (compare_date(temp_diary.date, longest_diary.date) > 0)
                longest_diary = temp_diary;
        }
    }
    return longest_diary;
}

note check_best_note(vector<note> notepad)
{
    int max_positive_words = 0;
    note best_diary;

    for (note temp_diary : notepad)
    {
        if (temp_diary.positive_word_count > max_positive_words)
        {
            max_positive_words = temp_diary.positive_word_count;
            best_diary = temp_diary;
        }
        else if (temp_diary.positive_word_count == max_positive_words)
        {
            if (compare_date(temp_diary.date, best_diary.date) > 0)
                best_diary = temp_diary;
        }
    }
    return best_diary;
}

void print_note(note text)
{
    int cnt_letters = 0;
    vector<char> letters(text.diary.begin(), text.diary.end() - 1); // for the last '\n'

    for (char ch : letters)
    {
        if (cnt_letters < MAX_LEN)
        {
            cout << ch;
            cnt_letters++;
        }
        else
        {
            cout << "...";
            break;
        }
    }
    cout << endl;
    return;
}

void add_note(string input, vector<string> positive_words, vector<note> &notepad)
{
    notepad.back().positive_word_count += is_positive(input, positive_words);

    char letter = getchar();

    notepad.back().diary += input;
    notepad.back().diary += letter;

    notepad.back().diary_length += input.size() + 1;
}

int compare_date(vector<int> date1, vector<int> date2)
{
    int age_gap;

    if ((age_gap = date2[2] - date1[2]) != 0)
        return age_gap;

    else if ((age_gap = date2[1] - date1[1]) != 0)
        return age_gap;

    else
        return age_gap = date2[0] - date1[0];
}
//
