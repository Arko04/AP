#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;

const vector<pair<string, string>> PERIOD =
    {{"07:30", "09:00"},
     {"09:30", "11:00"},
     {"11:30", "13:00"}};
const map<string, int> DAY =
    {{"Saturday", 0},
     {"Sunday", 1},
     {"Monday", 2},
     {"Tuesday", 3},
     {"Wednesday", 4}};
const int PERIOD_CNT = 3;
const int DAY_CNT = 5;
const int MAX_DAYS = 7;
const int CLASS_CNT = 2;
const string EMPTY = "";
typedef bool Period[DAY_CNT][PERIOD_CNT];

struct Index
{
    int cls;
    int day;
    int period;
};
struct Time
{
    string start;
    string end;
};
struct Course
{
    string name;
    Time time;
    string day[2];
    bool is_chosen[CLASS_CNT] = {false, false};
};
struct Tutor
{
    string name;
    bool is_teached[CLASS_CNT];
};
struct Teacher
{
    string name;
    int free_days_cnt;
    Period have_time;
    vector<Tutor> courses;
};
struct Class
{
    string course_name = EMPTY;
    string teacher_name = EMPTY;
    bool is_full = false;
};
typedef Class Plan[CLASS_CNT][DAY_CNT][PERIOD_CNT];

void print_plan(Plan plan)
{
    for (int clss = 0; clss < CLASS_CNT; clss++)
    {
        for (int day = 0; day < DAY_CNT; day++)
        {
            for (int period = 0; period < PERIOD_CNT; period++)
                cout << plan[clss][day][period].is_full << ' ';
            cout << endl;
        }
        cout << endl;
    }
    cout << "_________" << endl;
}

vector<string> input()
{
    string input;
    vector<string> inputList;
    while (getline(cin, input))
        {   if (input!="")
            inputList.push_back(input);}
    return inputList;
}
void valid_day(Teacher &teacher, string tutor_day)
{
    for (int period = 0; period < PERIOD_CNT; period++)
        teacher.have_time[DAY.at(tutor_day)][period] = true;
}
Teacher initialize_teacher_time()
{
    Teacher teacher;
    for (int day = 0; day < DAY_CNT; day++)
        for (int period = 0; period < PERIOD_CNT; period++)
            teacher.have_time[day][period] = false;
    return teacher;
}
Teacher initialize_teacher(string input_line)
{
    int course_cnt;
    string tutor_day, course;
    Teacher teacher = initialize_teacher_time();
    stringstream input(input_line);
    input >> teacher.name >> teacher.free_days_cnt;
    for (int j = 0; j < teacher.free_days_cnt; j++)
    {
        input >> tutor_day;
        valid_day(teacher, tutor_day);
    }
    input >> course_cnt;
    for (int j = 0; j < course_cnt; j++)
    {
        input >> course;
        teacher.courses.push_back({course, {true, true}});
    }
    return teacher;
}
void process_teacher(vector<string> &inputList, vector<Teacher> &teacherList)
{
    int teacher_cnt, i;
    stringstream input(inputList[0]);
    input >> teacher_cnt;
    for (i = 1; i <= teacher_cnt; i++)
    {
        Teacher teacher = initialize_teacher(inputList[i]);
        teacherList.push_back(teacher);
    }
    inputList.erase(inputList.begin(), inputList.begin() + i);
}
vector<Course> initialize_courses(vector<string> inputList, int course_cnt)
{
    vector<Course> courseList;
    for (int i = 1; i <= course_cnt; i++)
    {
        Course course;
        stringstream input(inputList[i]);
        input >> course.name >> course.day[0] >> course.day[1] >>
            course.time.start >> course.time.end;
        courseList.push_back(course);
    }
    return courseList;
}
void process_course(vector<string> inputList, vector<Course> &courseList)
{
    int course_cnt;
    stringstream input(inputList[0]);
    input >> course_cnt;
    courseList = initialize_courses(inputList, course_cnt);
}
void process_input(vector<string> inputList, vector<Teacher> &teacherList, vector<Course> &courseList)
{
    process_teacher(inputList, teacherList);
    process_course(inputList, courseList);
}
bool has_teacher_time(Period have_time, string day[2], int period)
{
    return have_time[DAY.at(day[0])][period] == true &&
           have_time[DAY.at(day[1])][period] == true;
}
bool is_teacher_valid(Course course, Teacher teacher, Index index)
{
    Tutor crs;
    bool is_crs_found = false;
    for (Tutor teacher_course : teacher.courses)
        if (teacher_course.name == course.name)
        {
            is_crs_found = true;
            crs = teacher_course;
            break;
        }
    if (is_crs_found == false)
        return false;
    if (crs.is_teached[index.cls] == false)
        return false;

    if (has_teacher_time(teacher.have_time, course.day, index.period) == false)
        return false;

    return true;
}
Teacher choose_teacher(Course course, vector<Teacher> teacherList, Index index)
{
    Teacher teacher = {.name = EMPTY, .free_days_cnt = MAX_DAYS};
    for (Teacher cur_teacher : teacherList)
        if (is_teacher_valid(course, cur_teacher, index))
        {
            if (cur_teacher.free_days_cnt < teacher.free_days_cnt)
                teacher = cur_teacher;
            if (cur_teacher.free_days_cnt == teacher.free_days_cnt)
                if (cur_teacher.name < teacher.name || teacher.name == EMPTY)
                    teacher = cur_teacher;
        }
    return teacher;
}
bool is_day_match(string day[2], int day_no)
{
    return day_no == DAY.at(day[0]) ||
           day_no == DAY.at(day[1]);
}
bool is_time_match(Time time, int period)
{
    return PERIOD[period].first >= time.start && PERIOD[period].second <= time.end;
}
bool is_plan_not_full(Plan plan, string day[2], Index index)
{
    return (plan[index.cls][DAY.at(day[0])][index.period].is_full == false &&
            plan[index.cls][DAY.at(day[1])][index.period].is_full == false);
}
bool is_course_free(Course &course, int cls)
{
    return (course.is_chosen[cls] == true) ? false : true;
}
bool is_valid_in_this_period(Plan &plan, Course course, Index index)
{
    if (is_day_match(course.day, index.day))
        if (is_time_match(course.time, index.period))
            if (is_plan_not_full(plan, course.day, index))
                if (is_course_free(course, index.cls))
                {
                    // print_plan(plan);
                    // cout << course.name << endl;
                    return true;
                }
    return false;
}
Class choose_course(Plan &plan, vector<Teacher> &teacherList,
                    vector<Course> &courseList, Index index, int i = 0)
{
    Class curr_cls, next_cls;

    if (i == courseList.size())
        return curr_cls;

    next_cls = choose_course(plan, teacherList, courseList, index, i + 1);
    if (!is_valid_in_this_period(plan, courseList[i], index))
        return next_cls;

    Teacher teacher = choose_teacher(courseList[i], teacherList, index);
    if (teacher.name == EMPTY)
        return next_cls;

    if (courseList[i].name > next_cls.course_name && next_cls.course_name != EMPTY)
        return next_cls;

    curr_cls.teacher_name = teacher.name;
    curr_cls.course_name = courseList[i].name;
    return curr_cls;
}
Course make_course_used(vector<Course> &courseList, string searched_course_name, int cls)
{
    for (Course &course : courseList)
        if (course.name == searched_course_name)
        {
            course.is_chosen[cls] = true;
            return course;
        }
    abort();
}
void make_teacher_time_full(Period &time, string day[2], int period)
{
    time[DAY.at(day[0])][period] = false;
    time[DAY.at(day[1])][period] = false;
}
void make_teacher_used_for_period(vector<Teacher> &teacherList,
                                  string searched_teacher_name, Course chosen_course, Index index)
{
    for (Teacher &teacher : teacherList)
        if (searched_teacher_name == teacher.name)
            for (Tutor &course : teacher.courses)
                if (course.name == chosen_course.name)
                {
                    make_teacher_time_full(teacher.have_time, chosen_course.day, index.period);
                    course.is_teached[index.cls] = false;
                    return;
                }
}
void make_used(vector<Teacher> &teacherList, vector<Course> &courseList, Plan &plan, Index index)
{
    Course chosen_course = make_course_used(courseList, plan[index.cls][index.day][index.period].course_name, index.cls);
    plan[index.cls][DAY.at(chosen_course.day[0])][index.period].is_full = true;
    plan[index.cls][DAY.at(chosen_course.day[1])][index.period].is_full = true;
    make_teacher_used_for_period(teacherList, plan[index.cls][index.day][index.period].teacher_name, chosen_course, index);
}
void plan_each_class(Plan &plan, vector<Teacher> &teacherList, vector<Course> &courseList, Index index)
{
    plan[index.cls][index.day][index.period] = choose_course(plan, teacherList, courseList, index);
    if (/*plan[index.cls][index.day][index.period].course_name != EMPTY && */ plan[index.cls][index.day][index.period].teacher_name != EMPTY)
    {
        // plan[index.cls][index.day][index.period].is_full = true;
        make_used(teacherList, courseList, plan, index);
        // print_plan(plan); 
    }
    // return fit_course;
}
void plan_classes(vector<Teacher> &teacheList, vector<Course> &courseList, Plan &plan)
{
    for (int clss = 0; clss < CLASS_CNT; clss++)
        for (int day = 0; day < DAY_CNT; day++)
            for (int period = 0; period < PERIOD_CNT; period++)
                if (plan[clss][day][period].is_full == false)
                    /*plan[clss][day][period] =*/plan_each_class(plan, teacheList, courseList, {clss, day, period});
}
vector<string> sort_course(vector<Course> courseList)
{
    vector<string> course_names;
    for (Course course : courseList)
        course_names.push_back(course.name);

    sort(course_names.begin(), course_names.end());
    return course_names;
}
void print_teacher(string teacher_name, int period)
{
    cout << teacher_name << ": " << PERIOD[period].first << ' ' << PERIOD[period].second << endl;
}
void output(Plan plan, vector<string> sorted_course_name)
{
    bool is_found;
    for (string course_name : sorted_course_name)
    {
        cout << course_name << endl;
        for (int clss = 0; clss < CLASS_CNT; clss++)
        {
            is_found = false;
            for (int day = 0; day < DAY_CNT; day++)
                for (int period = 0; period < PERIOD_CNT; period++)
                    if (plan[clss][day][period].course_name == course_name)
                    {
                        is_found = true;
                        print_teacher(plan[clss][day][period].teacher_name, period);
                    }
            if (is_found == false)
                cout << "Not Found\n";
        }
    }
}

void system()
{
    vector<string> inputList = input();
    vector<Teacher> teacherList;
    vector<Course> courseList;
    process_input(inputList, teacherList, courseList);
    Plan cls;
    plan_classes(teacherList, courseList, cls);
    vector<string> sorted_courses_name = sort_course(courseList);
    output(cls, sorted_courses_name);
}
int main() { system(); }
