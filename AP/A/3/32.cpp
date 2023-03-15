#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

const map<string, int> daysss= {{"Saturday", 0},{"Sunday", 1},{"Monday", 2},{"Tuesday", 3},{"Wednesday", 4}};
enum
{
    FIRST_PERIOD,
    SECOND_PERIOD,
    THIRD_PERIOD,
};
enum
{
    CLASS1,
    CLASS2,
};
struct Time
{
    string start;
    string end;
};
const vector<Time> TIME = {{"07:30", "09:00"}, {"09:30", "11:00"}, {"11:30", "13:00"}};

const int WEEKDAYS = 5;
const int CLASS_COUNT = 2;
const int PERIOD_COUNT = 3;
const int DAY_COUNT = 2;

struct Class
{
    string course;
    string teacher_name;
    bool is_filled = false;
};


    typedef Class DayPlan[PERIOD_COUNT] ;
    // vector<Class> class_period = vector< Class> (PERIOD_COUNT);

    typedef DayPlan weekPlan[5] ;

struct dayy{
    bool is_chosen[3];
};
struct Course
{
    string name;
    string day[2];//////
    map <string,dayy> is_chosen;////[DAY_COUNT]  ; /// add here
    Time time;
    // vector< Teacher> teachers; //////////
    bool is_chosen[CLASS_COUNT];
};

struct Teacher
{
    string name;
    int free_days_count;
    vector<string> free_days;
    // vector< vector<bool> >  is_reserved = 
    // vector < vector < bool> >(free_days_count, vector<bool>(3, false)); /////
    bool have_time[5][3];
    // map<string , dayy> is_reserved; // add here
    int courses_count;
    vector<string> courses;
};
// void print_teachers(vector <Teacher> teachers);

vector<Teacher> input_teachers_info()
{
    int teacher_count;
    string free_day, course;
    cin >> teacher_count;
    vector<Teacher> teacherList(teacher_count);
    for (int i = 0; i < teacher_count; i++)
    {
        cin >> teacherList[i].name >> teacherList[i].free_days_count;
        for (int j = 0; j < teacherList[i].free_days_count; j++)
        {
            cin >> free_day;
            teacherList[i].free_days.push_back(free_day);
        }
        cin >> teacherList[i].courses_count;
        for (int j = 0; j < teacherList[i].courses_count; j++)
        {
            cin >> course;
            teacherList[i].courses.push_back(course);
        }
    }
    return teacherList;
}

vector<Course> input_courses_info()
{
    int courses_count;
    cin >> courses_count;
    vector<Course> courseList(courses_count);
    for (int i = 0; i < courses_count; i++)
        cin >> courseList[i].name >>
            courseList[i].day[0] >> courseList[i].day[1] >>
            courseList[i].time.start >> courseList[i].time.end;

    return courseList;
}
// void print_teachers(vector <Teacher> teachers){
//     cout << teachers.size() << endl;
//     for(Teacher teacher: teachers)
//     {
//         cout << teacher.name << ' ' << teacher.free_days_count<<' ';
//         for(int i = 0; i < teacher.free_days_count; i++){
//             cout << teacher.free_days.at(i)<<' ';
//         }
//         cout << teacher.courses_count<<' ';
//         for(int i = 0; i < teacher.courses_count; i++){
//             cout << teacher.courses.at(i)<<' ';
//         }
//         cout << endl;
//     }
// }
// void print_courses(vector< Course> courses){
//     cout << courses.size()<<endl;
//     for(Course course: courses){
//         cout<< course.name << ' '<<
//         course.day[0] << ' '<<course.day[1]<<' '<<
//         course.time.start <<' '<<course.time.end << endl;
//     }
// }
int main()
{
    vector<Teacher> teachers = input_teachers_info();
    vector<Course> courses = input_courses_info();

    // print_teachers(teachers);
    // print_courses(courses);
    // vector< DayPlan > week_plan = plan_weekdays();
}

vector< weekPlan> v(vector<Teacher> teachers, vector<Course> courses)
{

    vector<weekPlan>  week_plan(2);
    for (int i = CLASS1; i <= CLASS2; i++)
    {
        // week_plan[i]=();  
    }
    return week_plan;
}

// class ha; 
// baraye har ostad 15 ta bool beirim
// 3( period_cnt) * 5(weekdays) va ba false por konim
// ba'd oon rooz ro true kon



/// map_name.find() for seaching if it is existed or not and doesn't add to the map
