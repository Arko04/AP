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

#define EQUAL 0

typedef struct note
{
    vector<int> date{DAY, MONTH, YEAR};
    int positive_word_count = 0;
    int diary_length = 0;
    string diary = "";
} note;

vector<string> reading_file_positive_words(string file_name);

void start_day(vector<note> &notepad);

void show_day(vector<note> notepad, note &searched_note, vector<int> &searched_day);

void show_the_longest_day(vector<note> notepad, note &longest_note);

void show_the_best_day(vector<note> notepad, note &best_note);

bool is_positive(string input_word, vector<string> positive_words);

void date_initialize(vector<int> &time);

note check_date(vector<note> notepad, vector<int> time);

note check_longest_note(vector<note> notepad);

note check_best_note(vector<note> notepad);

void check_max_value(note &main_note, note temp_note, int &max_value, int temp_value);

int compare_date(vector<int> date1, vector<int> date2);

void print_note(note text);

void print_date(vector<int> date);

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
        }
        else if (input == "show_day")
        {
            show_day(notepad, check_note, temp_day);
        }
        else if (input == "show_the_longest_day")
        {
            show_the_longest_day(notepad, check_note);
        }
        else if (input == "show_the_best_day")
        {
            show_the_best_day(notepad, check_note);
        }
        else
        {
            add_note(input, positive_words, notepad);
        }
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
    {
        positive_words.push_back(word);
    }

    input.close();
    return positive_words;
}

void start_day(vector<note> &notepad)
{
    notepad.resize(notepad.size() + 1);

    date_initialize(notepad.back().date);
}

void show_day(vector<note> notepad, note &searched_note, vector<int> &searched_day)
{
    date_initialize(searched_day);

    searched_note = check_date(notepad, searched_day);

    cout << searched_note.diary;
}

void show_the_longest_day(vector<note> notepad, note &longest_note)
{
    longest_note = check_longest_note(notepad);

    print_date(longest_note.date);
    print_note(longest_note);
}

void show_the_best_day(vector<note> notepad, note &best_note)
{
    best_note = check_best_note(notepad);

    print_date(best_note.date);
    print_note(best_note);
}

void date_initialize(vector<int> &time)
{
    vector<int> dates(3, 0);
    int index = 0;
    char letter;

    getchar();

    while (cin.get(letter))
    {
        switch (letter)
        {
        case DATE_DELIMITER:
            time.at(index) = dates.at(index);
            index++;
            break;
        case '\n':
        case ' ':
            time.at(index) = dates.at(index);
            return;
        default:
            dates.at(index) = dates.at(index) * 10 + (letter - '0');
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
        {
            return true;
        }
    }
    return false;
}

note check_date(vector<note> notepad, vector<int> time)
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

note check_longest_note(vector<note> notepad)
{
    int max_size = 0;
    note longest_diary;

    for (note temp_diary : notepad)
    {
        check_max_value(longest_diary, temp_diary, max_size, temp_diary.diary_length);
    }
    return longest_diary;
}

note check_best_note(vector<note> notepad)
{
    int max_positive_words = 0;
    note best_diary;

    for (note temp_diary : notepad)
    {
        check_max_value(best_diary, temp_diary, max_positive_words, temp_diary.positive_word_count);
    }
    return best_diary;
}

void check_max_value(note &main_note, note temp_note, int &max_value, int temp_value)
{
    if (temp_value > max_value)
    {
        max_value = temp_value;
        main_note = temp_note;
    }
    else if (temp_value == max_value)
    {
        if (compare_date(temp_note.date, main_note.date) > 0)
        {
            main_note = temp_note;
        }
    }
}

void print_note(note text)
{
    int cnt_letters = 0;
    vector<char> letters(text.diary.begin(), text.diary.end() - 1);

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

void print_date(vector<int> date)
{
    cout << date[DAY] << DATE_DELIMITER << date[MONTH] << DATE_DELIMITER << date[YEAR] << endl;
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

    if ((age_gap = date2.at(YEAR) - date1.at(YEAR)) != EQUAL);

    else if ((age_gap = date2.at(MONTH) - date1.at(MONTH)) != EQUAL);

    else
    {
        age_gap = date2.at(DAY) - date1.at(DAY);
    }
    return age_gap;
}
//
