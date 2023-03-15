#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map> ///////////////
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

// int day_to_int(string day){
//     const map<string, int> DAY = {{"Saturday", 0},
//                               {"Sunday", 1},
//                               {"Monday", 2},
//                               {"Tuesday", 3},
//                               {"Wednesday", 4}};
//     return DAY.at(day);
// }
typedef bool Period[3];

struct Time
{
    string start;
    string end;
};
struct Course
{
    string name;
    // bool is_tutored[2][5][3];
    Time time;
    string day[2];
    bool is_chosen[2] = {false, false};
    // map<string, Period> is_totured[2];
    // map< pair<string, string> , Period > is_tutored;
};
struct Teacher
{
    string name;
    // bool have_time[5][3];
    int free_days_cnt;
    Period have_time[5];
    // map<string, bool> course;
    vector<string> courses;
};

struct Class
{
    string course_name;
    string teacher_name;
    bool is_full;
};

typedef Class Plan[2][5][3];

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
    for (int i = 0; i < 3; i++)
        teacher.have_time[DAY.at(tutor_day)][i] = true;
}
Teacher initialize_teacher(string input_line)
{
    int course_cnt;
    string tutor_day, course;
    Teacher teacher;
    /// it can be function
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
            teacher.have_time[i][j] = false;
    }
    ///
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
    int teacher_cnt, i; //, free_days_cnt, course_cnt;
    // for (int i = 0; i < 5; i++){
    //     for(int j = 0; j < 3; j++)
    //     teacher.have_time[i][j] = false;
    // }
    // string tutor_day, course; /// index instead of 0
    stringstream input(inputList[0]);
    input >> teacher_cnt;
    // inputList.erase(inputList.begin());
    for (i = 1; i <= teacher_cnt; i++)
    { /// function initialize_teacher

        Teacher teacher = initialize_teacher(inputList[i]);
        //     for (int i = 0; i < 5; i++){
        //     for(int j = 0; j < 3; j++)
        //     teacher.have_time[i][j] = false;
        // }
        // ///
        //     stringstream input(inputList[0]);
        //     input >> teacher.name >> free_days_cnt;
        //     for (int j = 0; j < free_days_cnt; j++)
        //     {
        //         input >> tutor_day;
        //         valid_day(teacher, tutor_day);
        //     }
        //     input >> course_cnt;
        //     for (int j = 0; j < course_cnt; j++)
        //     {
        //         input >> course;
        //         teacher.courses.push_back (course);
        //     }
        teacherList.push_back(teacher);
    }
    inputList.erase(inputList.begin(), inputList.begin() + i);
}
// enum
// {
//     START,
//     END,
// };

// void make_tutorable_day(Course &course, string day[2], string time[2])
// {
//     for (int i = 0; i < 2; i++)
//     { // claass cnt
//         for (int j = 0; j < 2; j++)
//         { // day cnt
//             for (int k = 0; k < 3; k++)
//             { // period
//                 if (PERIOD[k].first < time[START] && PERIOD[k].second > time[END])
//                     course.is_tutored[i][DAY.at(day[j])][k] = true;
//             }
//         }
//     }
// }
void process_course(vector<string> inputList, vector<Course> &courseList)
{
    int course_cnt;
    // string day[2];
    // Time time;
    stringstream input(inputList[0]);
    input >> course_cnt;
    // courseList.erase(courseList.begin());
    for (int i = 1; i <= course_cnt; i++)
    {
    Course course;
        stringstream input(inputList[i]);
        input >> course.name >> course.day[0] >> course.day[1] >> course.time.start >> course.time.end;
        // make_tutorable_day(course, day, time);
        courseList.push_back(course);
        // courseList.erase(courseList.begin());
    }
}
void process_input(vector<string> inputList, vector<Teacher> &teacherList, vector<Course> &courseList)
{
    // int numberOfLine, numberOfCourses, index;
    // stringstream in(inputList[0]);
    // in >> numberOfLine;
    // inputList.erase(inputList.begin());
    // for(int i = 0; i < numberOfLine; i++){
    //     stringstream in(inputList[index]);
    // inputList.erase(inputList.begin());
    //     //
    // }
    // stringstream in(inputList[index]);
    // in >> numberOfCourses;
    // for(index++; index <= numberOfCourses; index++){
    //     stringstream in(inputList[index]);
    //     //
    // }
    process_teacher(inputList, teacherList);
    process_course(inputList, courseList);
}
////

////
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
        cout <<endl;
    }
}
void print_course(vector<Course> courseList)
{
    for (Course course : courseList)
    {
        cout << course.name << ' ' << 
        course.day[0] << ' ' << 
        course.day[1] << ' ' <<
         course.time.start << ' ' << 
         course.time.end<<endl;
    }
}
void plan_class(vector<Teacher> &teacheList, vector<Course> &courseList, Plan &cls)
{
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