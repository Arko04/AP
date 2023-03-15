#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;

const vector<pair<string, string>> PERIOD = {{"07:30", "09:00"},
                                             {"09:30", "11:00"},
                                             {"11:30", "13:00"}};

const map<string, int> DAY = {{"Saturday", 0},
                              {"Sunday", 1},
                              {"Monday", 2},
                              {"Tuesday", 3},
                              {"Wednesday", 4}};

typedef bool Period[3];

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
    bool is_chosen[2] = {false, false};
};
struct Teacher
{
    string name;
    int free_days_cnt;
    Period have_time[5];
    vector<string> courses;
};

struct Class
{
    string course_name;
    string teacher_name;
    bool is_full = false;
};
typedef Class DayPlan[3];
typedef DayPlan WeekPlan[5];
typedef WeekPlan Plan[2];

vector<string> input()
{
    string input;
    vector<string> inputList;
    while (getline(cin, input))
        inputList.push_back(input);
    return inputList;
}
void print_input(vector<string> inputs)
{
    for (string input : inputs)
        cout << input << endl;
}
void valid_day(Teacher &teacher, string tutor_day)
{
    for (int period = 0; period < 3; period++)
        teacher.have_time[DAY.at(tutor_day)][period] = true;
}
Teacher initialize_teacher(string input_line)
{
    int course_cnt;
    string tutor_day, course;
    Teacher teacher;
    for (int day = 0; day < 5; day++)
    {
        for (int period = 0; period < 3; period++)
            teacher.have_time[day][period] = false;
    }
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
        teacher.courses.push_back(course);
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

void process_course(vector<string> inputList, vector<Course> &courseList)
{
    int course_cnt;
    stringstream input(inputList[0]);
    input >> course_cnt;
    for (int i = 1; i <= course_cnt; i++)
    {
        Course course;
        stringstream input(inputList[i]);
        input >> course.name >> course.day[0] >> course.day[1] >> course.time.start >> course.time.end;
        courseList.push_back(course);
    }
}
void process_input(vector<string> inputList, vector<Teacher> &teacherList, vector<Course> &courseList)
{
    process_teacher(inputList, teacherList);
    process_course(inputList, courseList);
}

void print_teacher(vector<Teacher> &teacheList)

{
    cout << endl
         << endl;
    for (Teacher teacher : teacheList)
    {
        cout << teacher.name << endl;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 3; j++)
                cout << teacher.have_time[i][j] << ' ';

            cout << endl;
        }
        for (string course : teacher.courses)
        {
            cout << course << ' ';
        }
        cout << endl;
    }
}
void print_course(vector<Course> courseList)
{
    for (Course course : courseList)
    {
        cout << course.name << ' ' << course.day[0] << ' ' << course.day[1] << ' ' << course.time.start << ' ' << course.time.end << endl;
    }
}
// void plan_period(vector<Teacher> &teacherList, vector<Course> &courseList,Class &cls);

// void plan_day(vector<Teacher> &teacherList, vector<Course> &courseList,DayPlan &cls){
//     for(int i = 0 ; i < 3; i++)
//         plan_period(teacherList,courseList,cls[i]);

// }
// void plan(vector<Teacher> &teacherList, vector<Course> &courseList,WeekPlan &cls)
// {
//     for(int day = 0; day < 5; day++)
//         plan_day(teacherList,courseList,cls[day]);

// }
bool is_teacher_valid(Course course, Teacher teacher, int period)
{
    // day[0] & day[1]
    // bool is full
    // have this course or not
    int flag = 0; /// change the name and make it a function
    for (string course_name : teacher.courses)
        if (course_name == course.name)
            flag = 1;
    if (flag == 0)
        return false;

    if (teacher.have_time[DAY.at(course.day[0])][period] != true ||
        teacher.have_time[DAY.at(course.day[1])][period] != true)
        return false;

    return true;
    ///
}
Teacher choose_teacher(Course course, vector<Teacher> teacherList, Index index)
{
    Teacher teacher = {.name = "",.free_days_cnt = 6};

    // string teacher_name = "", next_teacher;
    // if (i == teacherList.size() - 1)
    //     return teacher;
    for (Teacher cur_teacher : teacherList)
    {

        if (is_teacher_valid(course, cur_teacher, index.period))
        {
            if (cur_teacher.free_days_cnt < teacher.free_days_cnt)
                teacher = cur_teacher;
            else if (cur_teacher.name < teacher.name)
                teacher = cur_teacher;
        }
    }
    return teacher;
    /////////////////////
}
bool is_valid_in_this_period(Plan &cls, Course course, Index index)
{
    if (index.day == DAY.at(course.day[0]) ||
        index.day == DAY.at(course.day[1]))
        if (PERIOD[index.period].first <= course.time.start &&
            PERIOD[index.period].second >= course.time.end)
            if (cls[index.cls][DAY.at(course.day[0])][index.period].is_full == false &&
                cls[index.cls][DAY.at(course.day[1])][index.period].is_full == false)
                return true;
    return false;
}

bool is_course_free(Course course, int cls)
{
    return (course.is_chosen[cls] == true) ? false : true;
}
Class choose_course(Plan &cls, vector<Teacher> &teacherList, vector<Course> &courseList, Index index, int i = 0)
{

    Class curr_cls; //= {{""}, {""}, false};

    if (i == courseList.size() - 1)
        return curr_cls;
    Class next_cls = choose_course(cls, teacherList, courseList, index, i + 1);
    if (!is_course_free(courseList[i], index.cls))
        return next_cls;
    if (!is_valid_in_this_period(cls, courseList[i], index))
        return next_cls;
    Teacher teacher = choose_teacher(courseList[i], teacherList, index); /// change the name
    if (teacher.name == "")
        return next_cls;

    curr_cls.teacher_name = teacher.name;

    if (courseList[i].name > next_cls.course_name && next_cls.course_name != "")
        return next_cls;

    curr_cls.course_name = courseList[i].name;
    return curr_cls;
}
Course make_course_used(vector<Course> &courseList, string searched_course_name, int cls)
{
    for (Course course : courseList)
        if (course.name == searched_course_name)
        {
            course.is_chosen[cls] = true; /////////////////
            return course;
        } //////////
        exit(EXIT_FAILURE);
}
void make_teacher_used_for_period(vector<Teacher> &teacherList, string searched_teacher_name, Course chosen_course, int period)
{
    for (Teacher teacher : teacherList)
    {
        for (string course_name : teacher.courses)
        {
            if (searched_teacher_name == course_name)
            {
                teacher.have_time[DAY.at(chosen_course.day[0])][period] = false;
                teacher.have_time[DAY.at(chosen_course.day[1])][period] = false;
                return;
            }
        }
    }
}

void make_used(vector<Teacher> &teacherList, vector<Course> &courseList, Class fit_course, Index index)
{
    Course chosen_course = make_course_used(courseList, fit_course.course_name, index.cls);
    make_teacher_used_for_period(teacherList, fit_course.teacher_name, chosen_course, index.period);
}

Class plan(Plan &cls, vector<Teacher> &teacherList, vector<Course> &courseList, Index index)
{
    Class fit_course = choose_course(cls, teacherList, courseList, index);
    if (fit_course.course_name != "" && fit_course.teacher_name != "")
    {
        fit_course.is_full = true;
        make_used(teacherList, courseList, fit_course, index);
    }
    // search_teach
    // search_course
    return fit_course;
    // Course curr_course = courseList[i];
    // Course next_course = choose_best_course(teacheList,courseList,index,++i );
    // if(is_valid(courseList[i]))
}
void plan_class(vector<Teacher> &teacheList, vector<Course> &courseList, Plan &cls)
{
    for (int clss = 0; clss < 2; clss++)
    {
        for (int day = 0; day < 5; day++)
        {
            for (int period = 0; period < 3; period++)
            {
                cls[clss][day][period] = plan(cls, teacheList, courseList, {clss, day, period});
            }
        }
    }
    // plan(teacheList, courseList, cls[i]);
}
// return plan
int main()
{
    vector<string> inputList = input();
    vector<Teacher> teacherList;
    vector<Course> courseList;
    process_input(inputList, teacherList, courseList);
    Plan cls;
    plan_class(teacherList, courseList, cls);
    // Plan cls[2];
    // plan_class(teacherList, courseList, cls[0]);
    // plan_class(teacherList, courseList, cls[1]);
    // typedef Class Plan[5][3];
    print_teacher(teacherList);
    print_course(courseList);
    print_input(inputList);
}