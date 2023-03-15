#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int WEEKDAYS = 5;

struct Class{
    string course;
    string teacher;
    bool is_filled = false;
};
struct DayPlan{
    Class class1;
    Class class2;
    Class class3;
};
struct Course
{
    string name;
    string day1, day2;
    string start_time;
    string end_time;
    // bool is_chosen = false;
};

struct Teacher
{
    string name;
    int free_days_count;
    vector<string> free_days;
    int courses_count;
    vector<string> courses;
};
void print_teachers(vector <Teacher> teachers);

void input_teachers_info(vector <Teacher>& teacherList)
{
    // int teacher_count;
    string free_day, course;
    // cin >> teacher_count;
    // vector<Teacher> teacherList(teacher_count);
    for (Teacher teacher : teacherList)
    {
        cin >> teacher.name >> teacher.free_days_count;
        cout << teacher.name <<' ' << teacher.free_days_count<< ' ';
        for (int i = 0; i < teacher.free_days_count; i++)
        { /// can we use insert????
        
            cin >> free_day;
            teacher.free_days.push_back(free_day);
            cout << teacher.free_days[i]<<' ';
        }
        cin >> teacher.courses_count;
        cout << teacher.courses_count<<' ';
        for (int i = 0; i < teacher.courses_count; i++)
        {
            cin >> course;
            teacher.courses.push_back(course);
            cout << teacher.courses[i]<<' ';
        }
        cout << teacher.name;
    }////
    print_teachers(teacherList);
    cout << teacherList[0].name<< teacherList[0].free_days_count<< endl;
    cout << teacherList[1].name<<endl;
    cout << teacherList.size() << ' ';
    for(Teacher teacher: teacherList)
    {
        cout << teacher.name << ' ' << teacher.free_days_count<<' ';
        for(int i = 0; i < teacher.free_days_count; i++){
            cout << teacher.free_days.at(i)<<' ';
        }
        cout << teacher.courses_count<<' ';
        for(int i = 0; i < teacher.courses_count; i++){
            cout << teacher.courses.at(i)<<' ';
        }
        cout << endl;
    }
////
    // return teacherList;
}

vector<Course> input_courses_info()
{
    int courses_count;
    cin >> courses_count;
    vector<Course> courseList(courses_count);
    for (Course course : courseList)
        cin >> course.name >>
            course.day1 >> course.day2 >>
            course.start_time >> course.end_time;

    return courseList;
}
void print_teachers(vector <Teacher> teachers){
    cout << teachers.size() << ' ';
    for(Teacher teacher: teachers)
    {
        cout << teacher.name << ' ' << teacher.free_days_count<<' ';
        for(int i = 0; i < teacher.free_days_count; i++){
            cout << teacher.free_days.at(i)<<' ';
        }
        cout << teacher.courses_count<<' ';
        for(int i = 0; i < teacher.courses_count; i++){
            cout << teacher.courses.at(i)<<' ';
        }
        cout << endl;
    }
}
void print_courses(vector< Course> courses){
    cout << courses.size()<<' ';
    for(Course course: courses){
        cout<< course.name << ' '<< 
        course.day1 << ' '<<course.day2<<' '<<
        course.start_time <<' '<<course.end_time << endl;
    }
}
int main()
{//
    int teacher_count;
    cin >> teacher_count;
    //
    // take input
    vector<Teacher> teachers (teacher_count);
    input_teachers_info(teachers);
    // vector<Teacher> teachers = input_teachers_info();
    // vector<Course> courses = input_courses_info();
    ////
    cout << teachers.size() << ' ';
    for(Teacher teacher: teachers)
    {
        cout << teacher.name << ' ' << teacher.free_days_count<<' ';
        for(int i = 0; i < teacher.free_days_count; i++){
            cout << teacher.free_days.at(i)<<' ';
        }
        cout << teacher.courses_count<<' ';
        for(int i = 0; i < teacher.courses_count; i++){
            cout << teacher.courses.at(i)<<' ';
        }
        cout << endl;
    }

    ///
    print_teachers(teachers);
    // print_courses(courses);
    // vector< DayPlan > week_plan = plan_weekdays();
}