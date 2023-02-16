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

vector<string> reading_file_positive_words(string filename);

int count_positive_words(string line, vector<string> positive_words);
int count_word_in_text(string line, string word);

void date_initialize(vector<int> &time);

note check_date(vector<note> notepad, vector<int> time);

note check_longest_note(vector<note> notepad);

note check_best_code(vector<note> notepad);

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
            notepad.resize(notepad.size() + 1);
            date_initialize(notepad.back().date);
        }
        else if (input == "show_day")
        {
            date_initialize(temp_day);
            check_note = check_date(notepad, temp_day);
            cout << check_note.diary;
        }
        else if (input == "show_the_longest_day")
        {
            check_note = check_longest_note(notepad);
            cout << check_note.date[DAY] << DATE_DELIMITER << 
                    check_note.date[MONTH] << DATE_DELIMITER << 
                    check_note.date[YEAR] << endl;
            print_note(check_note);
        }
        else if (input == "show_the_best_day")
        {
            check_note = check_best_code(notepad);
            cout << check_note.date[DAY] << DATE_DELIMITER << 
                    check_note.date[MONTH] << DATE_DELIMITER << 
                    check_note.date[YEAR] << endl;
            print_note(check_note);
        }
        else
            add_note(input, positive_words, notepad);
    }
    exit(EXIT_SUCCESS);
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

int count_word_in_text(string text, string word)
{
    regex words_regex(word);

    auto words_begin = sregex_iterator(text.begin(), text.end(), words_regex);
    auto words_end = sregex_iterator();

    return distance(words_begin, words_end);
}

void date_initialize(vector<int> &time)
{
    getchar();
    vector<int> dates(3, 0);
    int i = 0;
    char letter;

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

int count_positive_words(string line, vector<string> positive_words)
{
    transform(line.begin(), line.end(), line.begin(), ::tolower);

    int positive_word_count = 0;
    for (string word : positive_words)
    {
        positive_word_count += count_word_in_text(line, word);
    }
    return positive_word_count;
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
        if (temp_diary.diary_length > max_size)
        {
            max_size = temp_diary.diary_length;
            longest_diary = temp_diary;
        }
    }
    return longest_diary;
}

note check_best_code(vector<note> notepad)
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
    }
    return best_diary;
}

void print_note(note text)
{
    int cnt_letters = 0;
    vector<char> letters(text.diary.begin(), text.diary.end());

    for (char ch : letters)
    {
        if (cnt_letters < MAX_LEN)
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
    cout << endl;
    return;
}

void add_note(string input, vector<string> positive_words, vector<note> &notepad)
{
    string line = input;
    getline(cin, input);
    line += input;

    notepad.back().diary_length += line.size();
    notepad.back().positive_word_count += count_positive_words(line, positive_words);

    notepad.back().diary += line;
    notepad.back().diary += '\n';
}
//
