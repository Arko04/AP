#include <iostream>
#include <vector>
using namespace std;

struct Time{
    int hour;
    int minute;
};

struct Course{
    string name;
    string day1,day2;
    Time start_time;
    Time end_time;
};

struct Teacher {
    string name;
    int free_days_count;
    vector< string> free_days;
    int courses_count;
    vector<string> courses;
};