#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <cmath>

using namespace std;

const string EMPLOYEE_FILE = "/employees.csv";
const string SALARY_CONFIGS_FILE = "/salary_configs.csv";
const string TEAMS_FILE = "/teams.csv";
const string WORKING_HOURS_FLIE = "/working_hours.csv";

const string EMPLOYEE_NOT_FOUND = "EMPLOYEE_NOT_FOUND";
const string TEAM_NOT_FOUND = "TEAM_NOT_FOUND";
const string INVALID_INTERVAL = "INVALID_INTERVAL";
const string INVALID_ARGUMENTS = "INVALID_ARGUMENTS";
const string INVALID_LEVEL = "INVALID_LEVEL";
const string NO_BONUS_TEAMS = "NO_BONUS_TEAMS";
const string OK = "OK";
const string EMPTY = "";
const string NOT_CHANGED = "-";
const string NOT_APPLICABLE = "N/A";

const string JUNIOR = "junior";
const string SENIOR = "senior";
const string EXPERT = "expert";
const string TEAM_LEAD = "team_lead";

const char INTERVAL_DELIMETER = '-';
const char FIELD_DELIMETER = ',';
const char ID_DELIMETER = '$';
const char PERCENT = '%';

const int NOT_ATTENDED = -1;
const int NOT_CHANGE = -1;
const int MONTH = 30;
const int MAX_VAL = 100000;
const int MIN_VAL = -1;

const float PERCENTAGE = 100.0;

map<string, int> LEVEL =
    {{JUNIOR, 0},
     {SENIOR, 1},
     {EXPERT, 2},
     {TEAM_LEAD, 3}};

vector<string> split_by(char c, string str)
{
    vector<string> result;
    string word;

    stringstream input(str);
    while (getline(input, word, c))
        result.push_back(word);

    return result;
}

class Interval
{
public:
    Interval(int _start, int _end);

    void print_interval();

    bool is_interval_valid(int check_start, int check_end);
    bool is_in(int start_hour);

    int get_working_hours() { return (end - start); }

private:
    int start;
    int end;
};

Interval::Interval(int _start, int _end)
{
    start = _start;
    end = _end;
}

bool Interval::is_in(int start_hour)
{
    return start <= start_hour && end >= (start_hour + 1);
}

bool Interval::is_interval_valid(int check_start, int check_end)
{
    return check_start < start && check_end <= start ||
           check_start >= end && check_end > end;
}

void Interval::print_interval()
{
    cout << start << INTERVAL_DELIMETER << end << ' ';
}

typedef vector<Interval> Intervals;

class Level
{
public:
    Level();
    Level(string, int, int, int, int, int);
    void set_level(string, int, int, int, int, int);
    int cal_salary(int total_WH);
    void show_salary_config();

    int get_tax() { return tax_percentage; }
    string get_level() { return level; }

private:
    bool does_change(int argument) { return (argument != NOT_CHANGE); }
    string level;
    int base_salary;
    int salary_per_hour;
    int salary_per_extra_hour;
    int official_working_hours;
    int tax_percentage;
};

Level::Level() { set_level(EMPTY, 0, 0, 0, 0, 0); }

Level::Level(string _level,
             int _base_salary,
             int _salary_per_hour,
             int _salary_per_extra_hour,
             int _official_working_hours,
             int _tax_percentage)
{
    set_level(_level,
              _base_salary,
              _salary_per_hour,
              _salary_per_extra_hour,
              _official_working_hours,
              _tax_percentage);
}

void Level::set_level(string _level,
                      int _base_salary,
                      int _salary_per_hour,
                      int _salary_per_extra_hour,
                      int _official_working_hours,
                      int _tax_percentage)
{
    level = _level;
    if (does_change(_base_salary))
        base_salary = _base_salary;

    if (does_change(_salary_per_hour))
        salary_per_hour = _salary_per_hour;

    if (does_change(_salary_per_extra_hour))
        salary_per_extra_hour = _salary_per_extra_hour;

    if (does_change(_official_working_hours))
        official_working_hours = _official_working_hours;

    if (does_change(_tax_percentage))
        tax_percentage = _tax_percentage;
}

int Level::cal_salary(int total_WH)
{
    int salary = base_salary;
    if (total_WH > official_working_hours)
        salary += official_working_hours * salary_per_hour +
                  (total_WH - official_working_hours) * salary_per_extra_hour;
    else
        salary += total_WH * salary_per_hour;

    return salary;
}

void Level::show_salary_config()
{
    cout << "Base Salary: " << base_salary << endl
         << "Salary Per Hour: " << salary_per_hour << endl
         << "Salary Per Extra Hour: " << salary_per_extra_hour << endl
         << "Official Working Hours: " << official_working_hours << endl
         << "Tax: " << tax_percentage << PERCENT << endl;
}

class Employee
{
public:
    Employee(const int &_id, const string &_name, const int &_age, Level *_level);
    bool is_interval_valid(const int &day, const pair<int, int> &period);

    void report_salary(const int &bonus_percent);
    void add_interval(const int &day, const pair<int, int> &period);
    void add_team_id(const int &_team_id) { team_id = _team_id; }
    void report_employee_salary(const int &bonus_percent);
    void remove_intervals(const int &day);

    int cal_salary_parameters(const int &bonus_percent);

    int get_id() { return id; }
    int get_team_id() { return team_id; }
    string get_name() { return name; }
    Level *get_level() { return level; }
    int get_total_WH() { return total_WH; }
    int get_absent_days();
    int get_working_hours_of_a_day(const int &day);
    int get_employee_work_in_hour(const int &start_hour);

private:
    bool does_work_this_hour_in_day(const int &day, const int &start_hour);

    int cal_bonus(const int &bonus_percent, const int &salary);
    int cal_tax(const int &salary, const int &bonus);
    int cal_total_earning(const int &salary, const int &bonus, const int &tax);

    int id;
    string name;
    int age;
    Level *level;
    vector<Intervals> working_days = vector<Intervals>(MONTH + 1);
    int team_id = NOT_ATTENDED;
    int total_WH = 0;
    int salary = 0;
    int tax = 0;
    int bonus = 0;
    int total_earning = 0;
};

Employee::Employee(const int &_id, const string &_name, const int &_age, Level *_level)
{
    id = _id;
    name = _name;
    age = _age;
    level = _level;
}

void Employee::report_salary(const int &bonus_percent)
{
    cal_salary_parameters(bonus_percent);

    cout << "ID: " << id << endl
         << "Name: " << name << endl
         << "Total Working Hours: " << total_WH << endl
         << "Total Earning: " << fixed << setprecision(0) << total_earning << endl
         << "---" << endl;
}

void Employee::add_interval(const int &day, const pair<int, int> &period)
{
    Interval interval(period.first, period.second);
    working_days[day].push_back(interval);
    total_WH += interval.get_working_hours();
}

bool Employee::is_interval_valid(const int &day, const pair<int, int> &period)
{
    for (Interval interval : working_days[day])
        if (!interval.is_interval_valid(period.first, period.second))
            return false;

    return true;
}

int Employee::get_absent_days()
{
    int working_days_count = 0;
    for (int i = 1; i <= MONTH; i++)
        if (working_days[i].size() != 0)
            working_days_count++;

    return MONTH - working_days_count;
}

void Employee::report_employee_salary(const int &bonus_percent)
{
    cal_salary_parameters(bonus_percent);

    cout << "ID: " << id << endl
         << "Name: " << name << endl
         << "Age: " << age << endl
         << "Level: " << level->get_level() << endl
         << "Team ID: ";

    if (team_id == NOT_ATTENDED)
        cout << NOT_APPLICABLE << endl;
    else
        cout << team_id << endl;

    cout << "Total Working Hours: " << total_WH << endl
         << "Absent Days: " << get_absent_days() << endl
         << "Salary: " << salary << endl
         << "Bonus: " << bonus << endl
         << "Tax: " << tax << endl
         << "Total Earning: " << total_earning << endl;
}

int Employee::cal_bonus(const int &bonus_percent, const int &salary)
{
    bonus = round((bonus_percent * salary) / PERCENTAGE);
    return bonus;
}

int Employee::cal_tax(const int &salary, const int &bonus)
{
    tax = round(level->get_tax() * (salary + bonus) / PERCENTAGE);
    return tax;
}

int Employee::cal_total_earning(const int &salary, const int &bonus, const int &tax)
{
    total_earning = round((salary + bonus) - tax);
    return total_earning;
}

int Employee::cal_salary_parameters(const int &bonus_percent)
{
    salary = level->cal_salary(total_WH);
    bonus = cal_bonus(bonus_percent, salary);
    tax = cal_tax(salary, bonus);
    total_earning = cal_total_earning(salary, bonus, tax);
    return total_earning;
}

int Employee::get_working_hours_of_a_day(const int &day)
{
    int get_working_hours_of_a_day = 0;
    for (Interval interval : working_days[day])
        get_working_hours_of_a_day += interval.get_working_hours();
    return get_working_hours_of_a_day;
}

void Employee::remove_intervals(const int &day)
{
    for (Interval interval : working_days[day])
        total_WH -= interval.get_working_hours();
    working_days[day].clear();
}

bool Employee::does_work_this_hour_in_day(const int &day, const int &start_hour)
{
    for (Interval interval : working_days[day])
        if (interval.is_in(start_hour))
            return true;
    return false;
}

int Employee::get_employee_work_in_hour(const int &start_hour)
{
    int total_working_in_hour = 0;
    for (int day = 1; day <= MONTH; day++)
        if (does_work_this_hour_in_day(day, start_hour))
            total_working_in_hour++;

    return total_working_in_hour;
}

class Team
{
public:
    Team(const int &, const int &, vector<Employee *>, const int &, const int &);
    void report_team_salary();
    bool is_bonusable();

    void update_bonus(const int &_bonus_percent) { bonus_percent = _bonus_percent; }
    int get_members_total_WH();
    int get_team_id() { return id; }
    int get_bonus_percent() { return bonus_percent; }

private:
    bool are_members_WH_less_than_variance();
    string find_name_by_id(const int &id);

    int id;
    int head_id;
    vector<Employee *> members;
    int bonus_min_working_hours;
    int bonus_working_hours_max_variance;
    int bonus_percent = 0;
};

Team::Team(const int &_id,
           const int &_head_id,
           vector<Employee *> _members,
           const int &_bonus_min_working_hours,
           const int &_bonus_working_hours_max_variance)
{
    id = _id;
    head_id = _head_id;
    members = _members;
    bonus_min_working_hours = _bonus_min_working_hours;
    bonus_working_hours_max_variance = _bonus_working_hours_max_variance;

    for (Employee *emp : members)
        emp->add_team_id(id);
}

string Team::find_name_by_id(const int &id)
{
    for (Employee *emp : members)
        if (id == emp->get_id())
            return emp->get_name();
    return NULL;
}

int Team::get_members_total_WH()
{
    int total_members_WH = 0;
    for (Employee *emp : members)
        total_members_WH += emp->get_total_WH();
    return total_members_WH;
}

void Team::report_team_salary()
{
    string head_emp_name = find_name_by_id(head_id);
    int total_members_WH = get_members_total_WH();
    float average_member_WH = (float)total_members_WH / members.size();
    cout << "ID: " << id << endl
         << "Head ID: " << head_id << endl
         << "Head Name: " << head_emp_name << endl
         << "Team Total Working Hours: " << get_members_total_WH() << endl
         << "Average Member Working Hours: " << fixed << setprecision(1) << average_member_WH << endl
         << "Bonus: " << bonus_percent << endl
         << "---" << endl;
    for (Employee *emp : members)
    {
        cout << "Member ID: " << emp->get_id() << endl
             << "Total Earning: " << fixed << setprecision(0) << emp->cal_salary_parameters(bonus_percent) << endl
             << "---" << endl;
    }
}

bool Team::are_members_WH_less_than_variance()
{
    for (Employee *member : members)
        if (member->get_total_WH() >= bonus_working_hours_max_variance)
            return false;

    return true;
}

bool Team::is_bonusable()
{
    if (get_members_total_WH() > bonus_min_working_hours && are_members_WH_less_than_variance())
        return true;
    return false;
}

class Management
{
public:
    Management(const vector<Employee *> _emps, const vector<Team *> _teams, const vector<Level *> _levels);

    void get_command(const string &command);

private:
    bool is_level_name_not_possible(const string &level_name);
    bool is_time_not_valid(const int &start, const int &end) { return start < 0 || end > 24 || start >= end; }
    bool is_day_not_valid(const int &day) { return day < 1 || day > 30; }

    int get_bonus_percent(const int &emp_id);
    int get_working_hours_of_a_day(const int &day);
    vector<pair<int, double>> get_working_hours_of_days(const int &start_day, const int &end_day);
    vector<pair<int, double>> get_max_WH(const vector<pair<int, double>> &WH_per_days);
    vector<pair<int, double>> get_min_WH(const vector<pair<int, double>> &WH_per_days);
    vector<pair<int, double>> get_average_emp_in_hours(const int &start_period, const int &end_period);
    int get_employee_per_hour(const int &start_hour);
    void report_total_hours_per_day(const int &start_day, const int &end_day);

    void report_employee_salary(const int &emp_id);
    void report_salaries();
    void report_team_salary(const int &team_id);
    void report_employee_per_hour(const int &start_period, const int &end_period);
    void show_salary_config(const string &level_name);
    void update_salary_config(const string &line);
    void add_interval(const int &emp_id, const int &day, const int &period_start, const int &period_end);
    void delete_working_hours(const int &emp_id, const int &day);
    void update_team_bonus(const int &team_id, const int &bonus_percentage);
    vector<pair<int, int>> find_teams_for_bonus();
    void print_bonusable_teams(vector<pair<int, int>> bonusable_teams);

    void manage_report_employee_salary();
    void manage_report_team_salary();
    void manage_report_total_hours_per_day();
    void manage_report_employee_per_hour();
    void manage_show_salary_config();
    void manage_update_salary_config();
    void manage_add_working_hours();
    void manage_delete_working_hours();
    void manage_update_team_bonus();
    void manage_find_teams_for_bonus();

    Employee *find_member(const int &id);
    Team *find_team(const int &team_id);

    vector<Employee *> emps;
    vector<Team *> teams;
    vector<Level *> levels;
};

Management::Management(const vector<Employee *> _emps,
                       const vector<Team *> _teams,
                       const vector<Level *> _levels)
{
    emps = _emps;
    teams = _teams;
    levels = _levels;
}

bool Management::is_level_name_not_possible(const string &level_name)
{
    return (level_name != JUNIOR && level_name != SENIOR &&
            level_name != EXPERT && level_name != TEAM_LEAD);
}

int Management::get_bonus_percent(const int &emp_id)
{
    Employee *emp = find_member(emp_id);
    Team *team = find_team(emp->get_team_id());
    if (team == NULL)
        return 0;
    int bonus_percent = team->get_bonus_percent();
    return bonus_percent;
}

void Management::report_employee_salary(const int &emp_id)
{
    Employee *emp = find_member(emp_id);
    if (emp == NULL)
    {
        cout << EMPLOYEE_NOT_FOUND << endl;
        return;
    }
    int bonus_percent = get_bonus_percent(emp_id);
    emp->report_employee_salary(bonus_percent);
}

void Management::report_salaries()
{
    for (Employee *emp : emps)
    {
        int bonus_percent = get_bonus_percent(emp->get_id());
        emp->report_salary(bonus_percent);
    }
}

void Management::report_team_salary(const int &team_id)
{
    Team *team = find_team(team_id);
    if (team == NULL)
    {
        cout << TEAM_NOT_FOUND << endl;
        return;
    }
    team->report_team_salary();
}

int Management::get_working_hours_of_a_day(const int &day)
{
    int all_emps_working_hours_in_a_day = 0;
    for (Employee *emp : emps)
        all_emps_working_hours_in_a_day += emp->get_working_hours_of_a_day(day);

    return all_emps_working_hours_in_a_day;
}

vector<pair<int, double>> Management::get_working_hours_of_days(const int &start_day, const int &end_day)
{
    vector<pair<int, double>> working_hours_per_day;
    for (int day = start_day; day <= end_day; day++)
        working_hours_per_day.push_back({day, get_working_hours_of_a_day(day)});

    return working_hours_per_day;
}

vector<pair<int, double>> Management::get_max_WH(const vector<pair<int, double>> &WH_per_day)
{
    double most_wh = MIN_VAL;
    vector<pair<int, double>> max_WH;
    for (int i = 0; i < WH_per_day.size(); i++)
    {
        if (WH_per_day[i].second > most_wh)
        {
            max_WH.clear();
            most_wh = WH_per_day[i].second;
        }
        if (WH_per_day[i].second == most_wh)
            max_WH.push_back(WH_per_day[i]);
    }
    return max_WH;
}

vector<pair<int, double>> Management::get_min_WH(const vector<pair<int, double>> &WH_per_day)
{
    double least_wh = MAX_VAL;
    vector<pair<int, double>> min_WH;
    for (int i = 0; i < WH_per_day.size(); i++)
    {
        if (WH_per_day[i].second < least_wh)
        {
            min_WH.clear();
            least_wh = WH_per_day[i].second;
        }
        if (WH_per_day[i].second == least_wh)
            min_WH.push_back(WH_per_day[i]);
    }
    return min_WH;
}

void Management::report_total_hours_per_day(const int &start_day, const int &end_day)
{
    if (start_day > end_day || start_day < 1 || end_day > MONTH)
    {
        cout << INVALID_ARGUMENTS << endl;
        return;
    }
    vector<pair<int, double>> working_hours_of_days = get_working_hours_of_days(start_day, end_day);

    vector<pair<int, double>> max_WH = get_max_WH(working_hours_of_days);
    vector<pair<int, double>> min_WH = get_min_WH(working_hours_of_days);

    for (pair<int, int> working_day : working_hours_of_days)
    {
        cout << "Day #" << working_day.first << ": " << working_day.second << endl;
    }
    cout << "---" << endl;
    cout << "Day(s) with Max Working Hours:";
    for (pair<int, int> maxhw : max_WH)
        cout << ' ' << maxhw.first;
    cout << endl;
    cout << "Day(s) with Min Working Hours:";
    for (pair<int, int> minhw : min_WH)
        cout << ' ' << minhw.first;
    cout << endl;
}

int Management::get_employee_per_hour(const int &start_hour)
{
    int total_work_in_hour = 0;
    for (Employee *emp : emps)
        total_work_in_hour += emp->get_employee_work_in_hour(start_hour);
    return total_work_in_hour;
}

vector<pair<int, double>> Management::get_average_emp_in_hours(const int &start_period, const int &end_period)
{
    vector<pair<int, double>> average_employee_in_hour;
    for (int hour_i = start_period; hour_i < end_period; hour_i++)
    {
        double employee_per_hour = get_employee_per_hour(hour_i);
        double average_working_in_hour = employee_per_hour / MONTH;
        average_employee_in_hour.push_back({hour_i, average_working_in_hour});
    }
    return average_employee_in_hour;
}

void Management::report_employee_per_hour(const int &start_period, const int &end_period)
{
    if (is_time_not_valid(start_period, end_period))
    {
        cout << INVALID_ARGUMENTS << endl;
        return;
    }
    vector<pair<int, double>> average_employee_in_hour = get_average_emp_in_hours(start_period, end_period);

    vector<pair<int, double>> max_avg = get_max_WH(average_employee_in_hour);
    vector<pair<int, double>> min_avg = get_min_WH(average_employee_in_hour);

    for (pair<int, double> avg : average_employee_in_hour)
    {
        cout << avg.first << INTERVAL_DELIMETER << avg.first + 1 << ": "
             << fixed << setprecision(1) << avg.second << endl;
    }
    cout << "---" << endl;
    cout << "Period(s) with Max Working Employees:";
    for (pair<int, double> max : max_avg)
        cout << ' ' << max.first << INTERVAL_DELIMETER << max.first + 1;

    cout << endl;
    cout << "Period(s) with Min Working Employees:";
    for (pair<int, double> min : min_avg)
        cout << ' ' << min.first << INTERVAL_DELIMETER << min.first + 1;

    cout << endl;
}

void Management::show_salary_config(const string &level_name)
{
    if (is_level_name_not_possible(level_name))
    {
        cout << INVALID_LEVEL << endl;
        return;
    }
    levels[LEVEL[level_name]]->show_salary_config();
}

void Management::update_salary_config(const string &line)
{
    vector<string> fields = split_by(' ', line);
    string name = fields[0];
    if (is_level_name_not_possible(name))
    {
        cout << INVALID_ARGUMENTS << endl;
        return;
    }
    int base_sal = (fields[1] == NOT_CHANGED) ? NOT_CHANGE : stoi(fields[1]);
    int sal_per_hour = (fields[2] == NOT_CHANGED) ? NOT_CHANGE : stoi(fields[2]);
    int sal_per_extra_hour = (fields[3] == NOT_CHANGED) ? NOT_CHANGE : stoi(fields[3]);
    int official_WH = (fields[4] == NOT_CHANGED) ? NOT_CHANGE : stoi(fields[4]);
    int tax_percent = (fields[5] == NOT_CHANGED) ? NOT_CHANGE : stoi(fields[5]);

    levels.at(LEVEL[name])->set_level(name, base_sal, sal_per_hour, sal_per_extra_hour, official_WH, tax_percent);
    cout << OK << endl;
}

void Management::add_interval(const int &emp_id, const int &day, const int &period_start, const int &period_end)
{
    if (is_time_not_valid(period_start, period_end) || is_day_not_valid(day))
    {
        cout << INVALID_ARGUMENTS << endl;
        return;
    }
    Employee *emp = find_member(emp_id);
    if (emp != NULL)
    {
        if (emp->is_interval_valid(day, {period_start, period_end}))
        {
            emp->add_interval(day, {period_start, period_end});
            cout << OK << endl;
        }
        else
            cout << INVALID_INTERVAL << endl;
    }
    else
        cout << EMPLOYEE_NOT_FOUND << endl;
}

void Management::delete_working_hours(const int &emp_id, const int &day)
{
    Employee *emp = find_member(emp_id);
    if (emp == NULL)
    {
        cout << EMPLOYEE_NOT_FOUND << endl;
        return;
    }
    if (is_day_not_valid(day))
    {
        cout << INVALID_ARGUMENTS << endl;
        return;
    }
    emp->remove_intervals(day);
    cout << OK << endl;
}

void Management::update_team_bonus(const int &team_id, const int &bonus_percentage)
{
    Team *team = find_team(team_id);
    if (team == NULL)
    {
        cout << TEAM_NOT_FOUND << endl;
        return;
    }
    if (bonus_percentage < 0 || bonus_percentage > 100)
    {
        cout << INVALID_ARGUMENTS << endl;
        return;
    }
    team->update_bonus(bonus_percentage);
    cout << OK << endl;
}

void Management::manage_report_employee_salary()
{
    int emp_id;
    cin >> emp_id;
    report_employee_salary(emp_id);
}

void Management::manage_report_team_salary()
{
    int team_id;
    cin >> team_id;
    report_team_salary(team_id);
}

void Management::manage_report_total_hours_per_day()
{
    int start_day, end_day;
    cin >> start_day >> end_day;
    report_total_hours_per_day(start_day, end_day);
}

void Management::manage_report_employee_per_hour()
{
    int start_period, end_period;
    cin >> start_period >> end_period;
    report_employee_per_hour(start_period, end_period);
}

void Management::manage_show_salary_config()
{
    string level;
    cin >> level;
    show_salary_config(level);
}

void Management::manage_update_salary_config()
{
    cin.get();
    string line;
    getline(cin, line);
    update_salary_config(line);
}

void Management::manage_add_working_hours()
{
    int emp_id, day, start_period, end_period;

    cin >> emp_id >> day >> start_period >> end_period;
    add_interval(emp_id, day, start_period, end_period);
}

void Management::manage_delete_working_hours()
{
    int emp_id, day;
    cin >> emp_id >> day;
    delete_working_hours(emp_id, day);
}

void Management::manage_update_team_bonus()
{
    int team_id, bonus_percentage;
    cin >> team_id >> bonus_percentage;
    update_team_bonus(team_id, bonus_percentage);
}

void Management::print_bonusable_teams(vector<pair<int, int>> bonusable_teams)
{
    sort(bonusable_teams.begin(), bonusable_teams.end(), [](pair<int, int> &team1, pair<int, int> &team2)
         { return team1.second < team2.second || team1.second == team2.second && team1.first < team2.first; });
    if (bonusable_teams.empty())
        cout << NO_BONUS_TEAMS << endl;

    for (pair<int, int> bonusable_team : bonusable_teams)
        cout << "Team ID: " << bonusable_team.first << endl;
}

vector<pair<int, int>> Management::find_teams_for_bonus()
{
    vector<pair<int, int>> bonusable_teams;
    for (int i = 0; i < teams.size(); i++)
        if (teams[i]->is_bonusable())
            bonusable_teams.push_back({teams[i]->get_team_id(), teams[i]->get_members_total_WH()});
    return bonusable_teams;
}

void Management::manage_find_teams_for_bonus()
{
    vector<pair<int, int>> bonusable_teams = find_teams_for_bonus();
    print_bonusable_teams(bonusable_teams);
}

void Management::get_command(const string &command)
{
    if (command == "report_salaries")
        report_salaries();
    else if (command == "report_employee_salary")
        manage_report_employee_salary();
    else if (command == "report_team_salary")
        manage_report_team_salary();
    else if (command == "report_total_hours_per_day")
        manage_report_total_hours_per_day();
    else if (command == "report_employee_per_hour")
        manage_report_employee_per_hour();
    else if (command == "show_salary_config")
        manage_show_salary_config();
    else if (command == "update_salary_config")
        manage_update_salary_config();
    else if (command == "add_working_hours")
        manage_add_working_hours();
    else if (command == "delete_working_hours")
        manage_delete_working_hours();
    else if (command == "update_team_bonus")
        manage_update_team_bonus();
    else if (command == "find_teams_for_bonus")
        manage_find_teams_for_bonus();
}

Team *Management::find_team(const int &team_id)
{
    for (Team *team : teams)
        if (team_id == team->get_team_id())
            return team;
    return NULL;
}

Employee *Management::find_member(const int &id)
{
    for (Employee *emp : emps)
        if (id == emp->get_id())
            return emp;
    return NULL;
}

class Input
{
public:
    Input(const string &emp_file, const string &salary_file, const string &team_file, const string &WH_file);
    vector<Employee *> get_employees() { return emps; }
    vector<Team *> get_teams() { return teams; }
    vector<Level *> get_levels() { return levels; }

private:
    Employee *read_emp(const string &str);
    vector<Employee *> read_employees_info(const string &filename);

    Level *read_level(const string &line);
    vector<Level *> read_salary_configs_info(const string &salary_filename);

    Team *read_team(const string &line);
    vector<Team *> read_teams_info(const string &filename);

    Employee *find_member(const int &id);
    vector<int> str_to_int(const vector<string> &members);
    vector<Employee *> get_members_address(const vector<int> &members_id);

    void add_working_hours(vector<Employee *> emps, const string &filename);
    void add_interval_to_emp(vector<Employee *> emps, const string &line);

    vector<Employee *> emps;
    vector<Team *> teams;
    vector<Level *> levels;
};

Input::Input(const string &emp_file, const string &salary_file, const string &team_file, const string &WH_file)
{
    levels = read_salary_configs_info(salary_file);
    emps = read_employees_info(emp_file);
    teams = read_teams_info(team_file);
    add_working_hours(emps, WH_file);
}

Employee *Input::read_emp(const string &line)
{
    vector<string> fields = split_by(FIELD_DELIMETER, line);
    int id = stoi(fields[0]);
    string name = fields[1];
    int age = stoi(fields[2]);
    string level_name = fields[3];
    return new Employee(id, name, age, levels[LEVEL[level_name]]);
}

vector<Employee *> Input::read_employees_info(const string &filename)
{
    vector<Employee *> emps;
    ifstream input_csv(filename);
    string line;
    getline(input_csv, line);
    while (getline(input_csv, line))
        emps.push_back(read_emp(line));

    input_csv.close();

    return emps;
}

Level *Input::read_level(const string &line)
{
    vector<string> fields = split_by(FIELD_DELIMETER, line);
    string lev = fields[0];
    int base_sal = stoi(fields[1]);
    int sal_per_hour = stoi(fields[2]);
    int sal_per_extra_hour = stoi(fields[3]);
    int official_WH = stoi(fields[4]);
    int tax_percentage = stoi(fields[5]);

    return new Level(lev, base_sal, sal_per_hour, sal_per_extra_hour, official_WH, tax_percentage);
}

vector<Level *> Input::read_salary_configs_info(const string &filename)
{
    vector<Level *> levels(4);
    Level *level;
    ifstream input_csv(filename);
    string line;
    vector<string> fields;
    getline(input_csv, line);
    while (getline(input_csv, line))
    {
        level = read_level(line);
        levels[LEVEL[level->get_level()]] = level;
    }
    input_csv.close();

    return levels;
}

vector<int> Input::str_to_int(const vector<string> &members)
{
    vector<int> members_id;
    for (string member : members)
        members_id.push_back(stoi(member));
    return members_id;
}

Team *Input::read_team(const string &line)
{
    vector<string> fields = split_by(FIELD_DELIMETER, line);
    vector<string> mems = split_by(ID_DELIMETER, fields[2]);
    vector<int> members_id = str_to_int(mems);
    sort(members_id.begin(), members_id.end());
    vector<Employee *> members = get_members_address(members_id);

    int team_id = stoi(fields[0]);
    int head_id = stoi(fields[1]);
    int bonus_min_working_hours = stoi(fields[3]);
    int bonus_working_hours_max_variance = stoi(fields[4]);
    return new Team(team_id, head_id, members, bonus_min_working_hours, bonus_working_hours_max_variance);
}

vector<Team *> Input::read_teams_info(const string &filename)
{
    vector<Team *> teams;
    ifstream input_csv(filename);

    string line;
    getline(input_csv, line);
    while (getline(input_csv, line))
        teams.push_back(read_team(line));

    input_csv.close();
    return teams;
}

void Input::add_interval_to_emp(vector<Employee *> emps, const string &line)
{
    vector<string> fields = split_by(FIELD_DELIMETER, line);
    int emp_id = stoi(fields[0]);
    Employee *emp = this->find_member(emp_id);
    string period = fields[2];
    vector<string> period_fields = split_by(INTERVAL_DELIMETER, period);
    pair<int, int> interval(stoi(period_fields[0]), stoi(period_fields[1]));
    int day = stoi(fields[1]);
    emp->add_interval(day, interval);
}

void Input::add_working_hours(vector<Employee *> emps, const string &filename)
{
    ifstream input_csv(filename);

    string line;
    getline(input_csv, line);
    while (getline(input_csv, line))
        add_interval_to_emp(emps, line);

    input_csv.close();
}

Employee *Input::find_member(const int &id)
{
    for (Employee *emp : emps)
        if (id == emp->get_id())
            return emp;
    return NULL;
}

vector<Employee *> Input::get_members_address(const vector<int> &members_id)
{
    vector<Employee *> members;
    for (int id : members_id)
        members.push_back(find_member(id));
    return members;
}

void system(string directory)
{
    string emp = directory + EMPLOYEE_FILE;
    string configs = directory + SALARY_CONFIGS_FILE;
    string teams = directory + TEAMS_FILE;
    string WH = directory + WORKING_HOURS_FLIE;
    Input input(emp, configs, teams, WH);
    Management management(input.get_employees(), input.get_teams(), input.get_levels());
    string command;
    while (cin >> command)
        management.get_command(command);
}

int main(int argc, char **argv)
{
    string directory = argv[1];
    system(directory);
}
