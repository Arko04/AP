#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
using namespace std;

const string CMD_START_DAY = "start_day";
const string CMD_SHOW_DAY = "show_day";
const string CMD_SHOW_LONGEST_DAY = "show_the_longest_day";
const string CMD_SHOW_BEST_DAY = "show_the_best_day";

const int SUMMARY_LENGTH = 20;

struct diary_day {
	string date;
	vector<string> lines;
};

bool starts_with(string str, string prefix) {
	return str.substr(0, prefix.length()) == prefix;
}

int find_diary_day(vector<diary_day> diary, string date) {
	for (int i = 0; i < diary.size(); i++) {
		if (diary[i].date == date)
			return i;
	}
	return -1;
}
void add_diary_line(vector<diary_day>& diary, string current_day, string line) {
	int index = find_diary_day(diary, current_day);
	if (index == -1) {
		diary.push_back({current_day, {line}});
	} else {
		diary[index].lines.push_back(line);
	}
}

void print_diary_lines(vector<string> lines) {
	for (int i = 0; i < lines.size(); i++) {
		cout << lines[i] << endl;
	}
}

void print_diary_lines_summary(vector<string> lines) {
	int output_size = 0;
	for (int i = 0; i < lines.size(); i++) {
		if (output_size + lines[i].length() < SUMMARY_LENGTH) {
			cout << lines[i] << endl;
			output_size += lines[i].length();
		} else  {
			cout << lines[i].substr(0, SUMMARY_LENGTH - output_size) << "..." << endl;
			return;
		}
	}
}

void print_diary_day(vector<diary_day> diary, string date) {
	int index = find_diary_day(diary, date);
	if (index != -1) {
		print_diary_lines(diary[index].lines);
	}
}

void print_diary_day_summary(diary_day dd) {
    cout << dd.date << endl;
    print_diary_lines_summary(dd.lines);
}

void handle_start_day(string line, string& current_day) {
	current_day = line.substr(CMD_START_DAY.length() + 1);
}

void handle_show_day(vector<diary_day> diary, string line) {
	print_diary_day(diary, line.substr(CMD_SHOW_DAY.length() + 1));
}

int diary_length(diary_day dd) {
    int total_length = 0;
    for (int i = 0; i < dd.lines.size(); i++)
        total_length += dd.lines[i].length();
    return total_length;
}

void handle_show_longest_day(vector<diary_day> diary) {
    int longest_index;
    int max_length = 0;
    for (int i = 0; i < diary.size(); i++) {
        if (diary_length(diary[i]) > max_length) {
            longest_index = i;
            max_length = diary_length(diary[i]);
        }
    }
	print_diary_day_summary(diary[longest_index]);
}

void read_positive_words(vector<string>& positive_words) {
    ifstream pw_file("positive-words.txt");
    string word;
    while (pw_file >> word) {
        positive_words.push_back(word);
    }
    pw_file.close();
}

bool is_positive_word(vector<string> positive_words, string word) {
    for (string pw : positive_words) {
        if (pw == word)
            return true;
    }
    return false;
}
int diary_positive_count(vector<string> positive_words, diary_day dd) {
    int positive_count = 0;
    for (int i = 0; i < dd.lines.size(); i++) {
        for (int j = 0; j < dd.lines[i].length(); j++) {
            if (!isalpha(dd.lines[i][j])) {
                dd.lines[i][j] = ' ';
            } else {
                dd.lines[i][j] = tolower(dd.lines[i][j]);
            }
        }
        string word;
        istringstream iss(dd.lines[i]);
        while (iss >> word) {
            if (is_positive_word(positive_words, word))
                positive_count++;
        }
    }
    return positive_count;
}

void handle_show_best_day(vector<diary_day> diary, vector<string> positive_words) {
    int best_index;
    int max_positive_cnt = -1;
    for (int i = 0; i < diary.size(); i++) {
        int positive_count = diary_positive_count(positive_words, diary[i]);
        if ((positive_count > max_positive_cnt) ||
                ((positive_count == max_positive_cnt) && (diary[i].date < diary[best_index].date))) {
            best_index = i;
            max_positive_cnt = positive_count;
        }
    }
    print_diary_day_summary(diary[best_index]);
}


int main() {
    vector<string> positive_words;
    read_positive_words(positive_words);

	string line;
	string current_day;
	vector<diary_day> diary;

	while (getline(cin, line)) {
		if (starts_with(line, CMD_START_DAY)) {
			handle_start_day(line, current_day);
		} else 	if (starts_with(line, CMD_SHOW_DAY)) {
			handle_show_day(diary, line);
		} else 	if (starts_with(line, CMD_SHOW_LONGEST_DAY)) {
			handle_show_longest_day(diary);
        } else 	if (starts_with(line, CMD_SHOW_BEST_DAY)) {
            handle_show_best_day(diary, positive_words);
		} else {
			add_diary_line(diary, current_day, line);
		}
	}
}